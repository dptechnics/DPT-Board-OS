/**
 * DPTechnics Web IDE
 * 
 * Description: javascript backend for the DPTechnics WEB IDE. An 
 * educational and tincker IDE for the DPT-Board. 
 * 
 * Authors: Matthieu Calie, Daan Pape
 * Company: DPTechnics
 */

/* ----------------------------------------------- GLOBAL VARIABLES ------------------------------------- */

var viewModel = null;                   /* KnockoutJS viewmodel */
var menuBarClicked = false;             /* True if the menu bar is active */
var editor = null;                      /* The ACE text editor */
var rootPane;                           /* The root pane */
var rightPane;                          /* Pane containing project structure */
var developPane;                        /* Pane containg output and console */
var workspace = new IdeWorkspace();     /* All projects currently loaded in the IDE */
var saveChanges = true;                 /* True when workspace changes should be saved */  
var codeGeneration = true;              /* True when blockly must generate code */
var socket = null;                      /* Remote code execution websocket */

/* ---------------------------------------------- STATIC VARIABLES ------------------------------------- */

// Maps language names onto default file extensions 
var EXTENSIONS = {
    "javascript": "js",
    "html": "html",
    "css": "css"
};

// Maps language names onto ACE code assistance options
var ACEMODES = {
    "javascript": "ace/mode/javascript",
    "html": "ace/mode/html",
    "css": "ace/mode/css"
};

// The type of a file in the projects file structure 
var FILECAT = {
    "directory": 0,         /* File directory */
    "file": 1,              /* Normal file */
    "dependency": 2         /* Dependency directory */
};

/* --------------------------------------------- INTERNATIONALISATION ----------------------------------- */

// Instantiate localisation 
var i18n = new I18n({
    directory: "locales",
    locale: "en",
    extension: ".json"
});

/**
 * Change the UI locale
 * @param {string} locale - the new locale in two letters
 * @returns {boolean} returns false to prevent event propagation
 */
function setLang(locale) {
    viewModel.setLocale(locale);

    // Close navbar when open
    $(".navbar-collapse").stop().css({'height': '1px'}).removeClass('in').addClass("collapse");
    $(".navbar-toggle").stop().removeClass('collapsed');
    return false;
}

/* --------------------------------------- PROJECT STRUCTURE AND MANAGEMENT ------------------------------- */

/**
 * Represents an IDE project file
 */
function IdeFile() {
    return {
        filename: "",           /* The name of the file */
        filetype: "",           /* The type of the file */
        filecat: "",            /* The file category (directory, file, ...) */
        editor: "",             /* The file content itself */
        blockly: null,          /* The blockly content if any */
        blocklyvisible: true,   /* True if blockly was visible */
        acemode: "",            /* The mode of the ACE editor for this file */
        active: false,          /* True if this file is in the active tab */
        display: false,         /* True if this file is in the open tabs */
        parent: null            /* The parent of the file */
    };
}

/**
 * Represents an IDE project.
 */
function IdeProject() {
    return {
        name: "",               /* The project name */
        type: "",               /* The project type (robot, iot, html, ...) */
        files: []               /* The files in the project */
    };
}

/**
 * Represensts an IDE workspace
 */
function IdeWorkspace() {
    return {
        name: "",               /* The workspace name */
        opentab: null,          /* The file currently open in editor */
        projects: [],           /* The projects in this workspace */
        files: []              /* Files in the workspace not belonging to a project */
    };
}

/**
 * Save the complete IDE workspace to local storage. 
 */
function saveWorkspaceToLocalStorage()
{
    localStorage.setItem("__dpt_ide_workspace", saveCompleteWorkspace());
}

/**
 * Checks if there is a workspace present in local storage.
 * @returns {Boolean} true when a workspace is available in browser local storage.
 */
function isLocalStorageWorkspacePresent()
{
    return localStorage.getItem("__dpt_ide_workspace") !== null;
}

/**
 * Restore a workspace previously saved in localStorage.
 */
function restoreFromLocalStorage()
{
    
    var saved = localStorage.getItem("__dpt_ide_workspace");
    restoreCompleteWorkspace(saved);
}

/**
 * Create's a download so the user can save the file for use later. 
 */
function saveWorkspaceToDownload()
{
    var download = document.createElement('a');
    download.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(saveCompleteWorkspace()));
    download.setAttribute('download', 'dpt-workspace.json');
    download.click();
}

/**
 * Save the current active file to the workspace object.
 * @returns {IdeFile} the current version of a file in the editor
 */
function saveWorkingFile() {
    if(workspace.opentab !== null && saveChanges) {
        workspace.opentab.editor = editor.getSession().getValue();
        
        // Blockly is javascript only
        if(workspace.opentab.filetype === "javascript") {
            var xml = Blockly.Xml.workspaceToDom(Blockly.mainWorkspace);
            workspace.opentab.blockly = Blockly.Xml.domToText(xml);
        }
    }
}

/**
 * Display a file in the editor
 * @param {IdeFile} file the file to display in the editor
 */
function displayFile(file) {
    if(file !== null) {
        //TODO: restore editor pane visibility
        editor.setValue(file.editor);
        editor.session.setMode(file.acemode);
        
        // Blockly is javascript only
        if(file.filetype === "javascript" && file.blockly !== null) {
            var xml = Blockly.Xml.textToDom(file.blockly);
            Blockly.Xml.domToWorkspace(Blockly.mainWorkspace, xml);
        } else {
            Blockly.mainWorkspace.clear();
        }   
    }
}

/**
 * Add a file to the current workspace.
 * @param {IdeFile} file the file to add
 * @param {IdeProject} project the file is added to a project if given. 
 */
function addFileToWorkspace(file, project) {
    if (!project) {
        workspace.files.push(file);
    } else {
        project.files.push(file);
    }

    viewModel.updateView();
}

/**
 * Set a specific file active in the editor
 * @param {IdeFile} file the file to set active
 */
function setFileActive(file) {
    workspace.opentab = null;
    
    workspace.projects.forEach(function (project) {
        project.files.forEach(function (a_file) {
            if(file === a_file) {
                a_file.active = true;
                workspace.opentab = a_file;
            } else {
                a_file.active = false;
            }
        });
    });

    workspace.files.forEach(function (a_file) {
        if(file === a_file) {
            a_file.active = true;
            workspace.opentab = a_file;
        } else {
            a_file.active = false;
        }
    });    
    
    // Update the editor view 
    viewModel.updateView();
}

/**
 * Serialize the complete workspace. 
 * @return {string} the complete workspace in JSON format
 */
function saveCompleteWorkspace() {
    return JSON.stringify(workspace);
}

/**
 * Restore a complete Ide workspace given a workspace file. 
 * @param {string} saved the serialized workspace
 */
function restoreCompleteWorkspace(saved) {
    workspace = JSON.parse(saved);

    // Turn of change listeners
    saveChanges = false;
    codeGeneration = false;
    
    // Update view
    viewModel.updateView();
    
    // Turn change listeners back on
    saveChanges = true;
    codeGeneration = true;
}

/* --------------------------------------- VISUALISATION CODE ------------------------------- */

/**
 * The system global viewmodel
 * @returns {GlobalViewModel}
 */
function ViewModel()
{
    /* -------------------------------- CODE ASSISTANCE -------------------------------- */
    this.codeAnnotations = ko.observableArray();

    /**
     * Removes all currently visible assistance messages
     */
    this.resetErrors = function () {
        this.codeAnnotations.removeAll();
    };

    /**
     * Add a code assistance object 
     * @param {type} obj the ACE code assistance object
     */
    this.addError = function (obj) {
        this.codeAnnotations.push(obj);
    };

    /* -------------------------------- PROJECT STRUCTURE -------------------------------- */

    /* Open file tabs in the ide */
    this.opentabs = ko.observableArray([]);

    /**
     * The UI based on the current workspace
     */
    this.updateView = function () {
        // Array containing the new tab configuration
        var newTabContext = [];

        // Search for all tabs in the workspace
        workspace.projects.forEach(function (project) {
            project.files.forEach(function (file) {
                if (file.display) {
                    newTabContext.push(file);

                    if (file.active) {
                        workspace.opentab = file;
                    }
                }
            });
        });

        workspace.files.forEach(function (file) {
            if (file.display) {
                newTabContext.push(file);

                if (file.active) {
                    workspace.opentab = file;
                }
            }
        });

        // Visualize
        this.opentabs.removeAll();
        this.opentabs(newTabContext);
        displayFile(workspace.opentab);
    };

    /* ----------------------------- I18N AND APP SETTINGS ----------------------------- */
    this.lang = ko.observable("en");
    this.title = ko.computed(function () {
        i18n.setLocale(this.lang());
        return i18n.__("AppName");
    }, this);

    /**
     * Change the UI locale
     * @param {string} locale - the new UI locale
     */
    this.setLocale = function (locale) {
        this.lang(locale);
        i18n.setLocale(this.lang());
    };
}

/* --------------------------------------- REMOTE CODE EXECUTION ------------------------------- */

/**
 * Retreive the correct websocket URL. 
 * @return {String} the URL to make a websocket connection to. 
 */
function rem_code_get_websocket_url()
{
    var url = document.URL;
    
    // Remove everything after hashtag
    var ht = url.indexOf('#');
    if(ht != -1) {
        url = url.substr(0, ht);
    }
    
    if(url[4] == 's') {
        return 'wss://' + url.substr(8) + "/ws";
    } else {
        return 'ws://' + url.substr(7) + '/ws';
    }
}

/**
 * Execute code on the remote interpreter
 * @param {String} code the code to execute. 
 * @returns {void}
 */
function rem_code_exec(code)
{
    // Stop previous code
    rem_code_stop();
    
    socket = new WebSocket(rem_code_get_websocket_url(), "ide-run");
    
    try {
        socket.onopen = function() {
            console.log('[INFO] DPT-Web IDE opened socket to remote interpreter');
            socket.send(code);
        };
        
        socket.onmessage = function(msg) {
            var csl = $('#console-pnl');
            $('#console-pnl-out').append(msg.data);
            var height = csl[0].scrollHeight;
            csl.scrollTop(height);
        };
       
        socket.onclose = function() {
            console.log('[INFO] DPT-Web IDE remote interpreter socket closed');
        };
    } catch(ex) {
        return NULL;
    }
}

/**
 * Stop code that is currently executing on the target.
 * @returns {void}
 */
function rem_code_stop()
{
    if(socket != null) {
        socket.close();
    }
}

/* --------------------------------------- INITIALISATION AND HANDLERS ------------------------------- */

$('document').ready(function () {
    DPT_AJAX_PREFIX = "/";

    /* -------------------------- Knockout GUI initialisaton ---------------------------- */
    viewModel = new ViewModel();
    ko.applyBindings(viewModel, document.getElementById("htmldoc"));

    /* -------------------------- Split panes initialisation ----------------------------- */
    rootPane = $('#splitpane').split({
        orientation: 'vertical',
        limit: 0,
        position: '15%'
    });

    rightPane = $('#horizontal-splitpane').split({
        orientation: 'horizontal',
        limit: 0,
        position: '80%'
    });

    developPane = $('#develop-split-pane').split({
        orientation: 'vertical',
        limit: 0,
        position: '50%'
    });

    /* -------------------------- Ace editor initialisation ------------------------------- */
    ace.require("ace/ext/language_tools");
    editor = ace.edit("language-editor");
    editor.session.setMode("ace/mode/javascript");
    editor.setTheme("ace/theme/twilight");

    // Enable autocompletion and snippets
    editor.setOptions({
        enableBasicAutocompletion: true,
        enableSnippets: true,
        enableLiveAutocompletion: false,
        fontSize: "14pt"
    });

    /* ------------------------ Menu structure initialisation ----------------------------- */
    $('.menu-title').click(function (e) {
        e.stopPropagation();
        if (menuBarClicked) {
            hideMenu();
            menuBarClicked = false;
        } else {
            showMenu($(this).parent('li').children('.menu-body'));
            menuBarClicked = true;
        }
    });

    $('.menu-title').mouseenter(function () {
        if (menuBarClicked) {
            showMenu($(this).parent('li').children('.menu-body'));
        }
    });

    $('body').click(function () {
        hideMenu();
        menuBarClicked = false;
    });

    /* ----------------------------- Menu Handlers ------------------------------------- */
    $('.menu-save').click(function () {

    });

    $('.menu-save-as').click(function () {

    });

    $('.menu-save-all').click(function () {

    });

    $('.menu-exit').click(function () {
        window.close();
    });

    $('.menu-cut').click(function () {

    });

    $('.menu-copy').click(function () {

    });

    $('.menu-paste').click(function () {

    });

    $('.menu-select-all').click(function () {

    });

    $('.menu-tutorials').click(function () {

    });

    $('.menu-help-index').click(function () {

    });

    $('.menu-check-updates').click(function () {

    });

    $('.menu-about').click(function () {

    });

    $('.open-project-explorer').click(function () {
        $('#project-explorer').css('min-width', '150px');
        rootPane.position('15%');
    });

    $('.close-project-explorer').click(function () {
        $('#project-explorer').css('min-width', '0px');
        rootPane.position('0%');
    });

    $('.open-error-list').click(function () {
        rightPane.position('80%');
    });

    $('.close-error-list').click(function () {
        rightPane.position('100%');
    });

    /* ----------------------------- BUTTON HANDLERS ------------------------------------- */
    
    /**
     * Handler for the fullscreen button
     */
    $('.btn-fullscreen').click(function () {
        if ((document.fullScreenElement && document.fullScreenElement !== null) || (!document.mozFullScreen && !document.webkitIsFullScreen)) {
            if (document.documentElement.requestFullScreen) {
                document.documentElement.requestFullScreen();
            } else if (document.documentElement.mozRequestFullScreen) {
                document.documentElement.mozRequestFullScreen();
            } else if (document.documentElement.webkitRequestFullScreen) {
                document.documentElement.webkitRequestFullScreen(Element.ALLOW_KEYBOARD_INPUT);
            }
        } else {
            if (document.cancelFullScreen) {
                document.cancelFullScreen();
            } else if (document.mozCancelFullScreen) {
                document.mozCancelFullScreen();
            } else if (document.webkitCancelFullScreen) {
                document.webkitCancelFullScreen();
            }
        }
    });

    $('.btn-undo').click(function () {
        editor.undo();
    });

    $('.btn-redo').click(function () {
        editor.redo();
    });

    $('.btn-text-mode').click(function () {
        changeDevelopMode(this, 0);
    });

    $('.btn-design-mode').click(function () {
        changeDevelopMode(this, 1);
    });

    $('.btn-splitview-mode').click(function () {
        changeDevelopMode(this, 2);
    });
    
    
    
    
    /**
     * Execute the code currently in the editor
     */
    $('.btn-play').click(function () {
        var source = editor.getValue();
        rem_code_exec(source);
    });
    
    /**
     * Stop remote code execution
     */
    $('.btn-halt').click(function(){
        rem_code_stop();
    });
    
    /**
     * TODO make preference 
     */
    changeDevelopMode($('.btn-text-mode'), 0);

    $('.btn-error-list').click(function () {
        $('.btn-console').removeClass('active');
        $('.btn-error-list').addClass('active');
        $('.error-list-pnl').removeClass('hidden');
        $('.console-pnl').addClass('hidden');
    });
    $('.btn-console').click(function () {
        $('.btn-console').addClass('active');
        $('.btn-error-list').removeClass('active');
        $('.error-list-pnl').addClass('hidden');
        $('.console-pnl').removeClass('hidden');
    });

    /* ---------------------------------- DIALOG BUTTON HANDLERS ---------------------------------- */
    
    /**
     * Handles the creation of a new file.
     */
    $('#new-file-dlg-create-btn').click(function() {
        //TODO: ask to add to existing project
        var name = $('#new-file-dlg form').find('input[name="filename"]').val();
        var lang = $('#new-file-dlg form').find('select[name="filetype"]').val();

        // Add extension to name 
        name = name + "." + EXTENSIONS[lang];

        // Construct the file
        var file = new IdeFile();
        file.filename = name;
        file.filetype = lang;
        file.filecat = FILECAT.file;
        file.acemode = ACEMODES[lang];

        // New files are opened in editor by default
        file.active = true;
        file.display = true;
        
        // Add file to correct project
        workspace.files.push(file);
        
        // Set file active and update view
        setFileActive(file);
        
        // Close dialog
        window.location.hash = "#close";
    });
    
    /**
     * Handles the storage of workspaces
     */
    $('#save-workspace-dlg').click(function() {
        var savemode = $('#save-workspace-dlg form').find('input:radio[name="storagetype"]:checked').val();
        
        switch (savemode) {
            case "localstorage":
                saveWorkspaceToLocalStorage();
                break;
            case "download":
                saveWorkspaceToDownload();
                break;
            case "onboard":
                break;
        }
        
        // Close dialog
        window.location.hash = "#close";
    });
    
    /**
     * Handles opening of a workspace.
     */
    $('#open-workspace-dlg').click(function() {
        restoreFromLocalStorage();
        
        // Close dialog
        window.location.hash = "#close";
    });
    
    /**
     * Handles a file upload
     * @param {JQuery Event} evt the event containing the target upload. 
     */
    $('#open-workspace-file-select').change(function(evt){
        var filelist = evt.target.files;
        
        if(filelist.length > 0) {
            var file = filelist[0];
            var reader = new FileReader();
            
            // Async handler when file is read
            reader.addEventListener("load", function(evt){
                var filecontent = evt.target.result;
                
                // Restore the workspace
                restoreCompleteWorkspace(filecontent);
                
                // Close dialog
                window.location.hash = "#close";
            });
            
            // Read the file
            reader.readAsText(file);
        }
    });

    /* ---------------------------------- ACE EDITOR EVENTS ---------------------------------- */
    $('.changeFontSize').click(function () {
        changeFontSize($('.changeFontSize').val());
    });

    // Update the code assistance values in the viewmodel
    editor.getSession().on("changeAnnotation", function () {
        var annot = editor.getSession().getAnnotations();
        viewModel.resetErrors();

        for (var key in annot) {
            if (annot.hasOwnProperty(key))
                viewModel.addError(annot[key]);
        }
    });
    
    editor.getSession().on("change", function() {
        // Save code in IDE objects
        saveWorkingFile();
    });

    /* ---------------------------------- BLOCKLY GUI EDITOR ---------------------------------- */
    Blockly.inject(document.getElementById('blockly-editor'),
            {toolbox: document.getElementById('toolbox')});

    // Listen to blockly internal changes
    function blocklyUpdateHandler() {
        if(codeGeneration && workspace.opentab !== null && workspace.opentab.filetype === "javascript") {
            var code = Blockly.JavaScript.workspaceToCode();
            editor.setValue(code);
        }
    }
    Blockly.addChangeListener(blocklyUpdateHandler);

    // Update blockly window size on browser window resize
    window.onresize = function (event) {
        Blockly.fireUiEvent(window, 'resize');
    };
});

/* --------------------------------------- DPT IDE SPECIFIC FUNCTIONS ------------------------------- */

/**
 * Handler for the tabswitches above the editor.
 * @param {IdeFile} file the file to switch to
 */
function tabswitch(file) {
    // Turn of save changes and code generation
    saveChanges = false;
    codeGeneration = false;
    
    // Set the file active 
    setFileActive(file);
    
    // Start listening to changes again
    saveChanges = true;
    codeGeneration = true;
}

/**
 * Show a specific menu.
 * @param {DOM element} menu the menu to be displayed.
 */
function showMenu(menu) {
    $('.menu-body').removeClass('menu-body-visible');
    $(menu).addClass('menu-body-visible');
}

/**
 * Hide all menus.
 */
function hideMenu() {
    $('.menu-body').removeClass('menu-body-visible');
}

/**
 * Switch from develop mode between full code view, full blockly view or split code/blockly view. 
 * @param {DOM element} button the button to set as active. 
 * @param {int} mode the mode to switch to (0 = fullcode, 1 = split code/blockly, 2 = fullblockly)
 */
function changeDevelopMode(button, mode) {
    $(button).parent().find('li.active').removeClass('active');
    $(button).addClass('active');

    if (mode === 0) {
        developPane.position('100%');
    } else if (mode === 1) {
        developPane.position('0%');
    } else {
        developPane.position('50%');
    }
}

/**
 * Set the font size of the ACE editor
 * @param {integer} size the size in points of the editor font
 */
function changeFontSize(size) {
    editor.setOptions({fontSize: size + "pt"});
}