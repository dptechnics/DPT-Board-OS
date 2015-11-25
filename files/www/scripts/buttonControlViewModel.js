/**
 * The page viewmodel, gvm is auto-instantiated in global.js
 * @param {Knockout viewmodel} gvm description: the global knockout viewmodel
 * @returns {void}
 */
function pageViewModel(gvm) {
    // Page title
    gvm.title = ko.computed(function(){i18n.setLocale(gvm.lang()); return gvm.app() + " - " + i18n.__("ButtoncontrolTitle");}, gvm);

    // The IO buttons observable array
    gvm.buttons = ko.observableArray([]);

    /**
     * Add an IO button to the viewmodel
     * @param {integer} btnr - the number of the button to add. 
     * @returns {void}
     */
    gvm.addIOButton = function(btn)
    {
        // Fill up the template
        gvm.buttons.push({
            number: btn.number,
            state : ko.observable(btn.state)
        });

        // Attach a handler to button
        $('#iobutton-' + btn.number).bind('switch-change', function(event, data){
            // Set the IO port on the new state
            dpt_setIO(btn.number, data.value);
        });
    };
    
    /**
     * Update the button state in the viewmodel.
     * @param {type} btn the btn state to update
     * @param {integer
     * @returns {undefined}
     */
    gvm.updateIOButton = function(btn, index)
    {
        gvm.buttons()[index].state(btn.state);
    };
    
    /**
     * Pulse an IO port for a given number of seconds read from
     * the input with id "pulsetime-<btnnumber>".
     * @param {object} btn the button to pulse. 
     * @returns {undefined}
     */
    gvm.pulseIOHandler = function(btn)
    {
        var time = $('#pulsetime-' + btn.number).val();
        
        dpt_pulseIO(btn.number, GPIO_ACT_HIGH, time, function() {
            BootstrapDialog.alert("Could not pulse IO port");
        });
    };
}

/* 
 * Set the state of a button.
 * @btnr: the number of the button. 
 * @state: the new button state.
 */
function setIOBtnState(btnr, state)
{
    $('#iobutton-' + btnr).bootstrapSwitch('setState', state);
}

/**
 * This function is called after system initalisation and will
 * be called on a regular basis.
 * @param {function} callback {function} call with true or false, on false polling will stop
 * @returns {void}
 */
function updateInfo(callback) {
    dpt_getIOOverview(function(nrports, ports){
        // Add a button for every port 
        for(i = 0; i < nrports; ++i) {
            // Update HTML
            viewModel.updateIOButton(ports[i], i);
        }
        callback(true);
    }, function() {
        console.log("Could not read IO port state");
        callback(true);
    });
}

/**
 * Automatically called page initialisation.
 * @returns {void}
 */
function initPage() {
    dpt_getIOOverview(function(nrports, ports){
        // Add a button for every port 
        for(i = 0; i < nrports; ++i) {
            // Append button to HTML DOM
            viewModel.addIOButton(ports[i]);
        }
    });
}