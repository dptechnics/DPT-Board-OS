/**
 * The page viewmodel, this is auto-instantiated in global.js
 * @param {Knockout viewmodel} gvm - the global knockout viewmodel
 * @returns {void}
 */
function pageViewModel(gvm) {
    // Page title
    gvm.title = ko.computed(function(){i18n.setLocale(gvm.lang()); return gvm.app() + " - " + i18n.__("FirmwareSettings");}, gvm);

    // Page buttons 
    gvm.firmwareStatusTitle = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareStatus");}, gvm);
    gvm.firmwareCheckBtn = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareCheckBtn");}, this);
    
    gvm.firmwareStatus = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareUpToDate");}, gvm);
    gvm.firmwareRelease = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareRelease");}, gvm);
    gvm.firmwareVersion = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareVersion");}, gvm);
    gvm.firmwareChangelog = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareChangelog");}, gvm);
    
    gvm.firmwareDownloadBtn = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareDownloadBtn");}, gvm);
    gvm.firmwareDownloadInfo = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareDownloadInfo");}, gvm);
    gvm.firmwareInstallBtn = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareInstallBtn");}, gvm);
    gvm.firmwareInstallInfo = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareInstallInfo");}, gvm);
    gvm.firmwareKeepSettings = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareKeepsettingsInfo");}, gvm);
    gvm.firmwareActionsTitle = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareActionsTitle");}, gvm);
    
    gvm.firmwareDownloaded = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("FirmwareDownloaded");}, gvm);
    
    /* Data bindings */
    gvm.uptodate = ko.observable(false);
    gvm.releasedate = ko.observable("");
    gvm.version = ko.observable("");
    gvm.changelog = ko.observableArray([]);
    gvm.downloaded = ko.observable(false);
    
    /**
     * Add a changelog entry to the observable array
     * @param {type} ch the changelog entry
     */
    gvm.addFirmwareChange = function(entry){
        gvm.changelog.push({ change: entry });
    }
    
    /**
     * Clear the list of changes 
     */
    gvm.clearChangelist = function() {
        gvm.changelog.removeAll();
    }
    
    /* Up to date info text binding and style binding */
    gvm.firmwareStatusLabel = ko.computed(function(){
        i18n.setLocale(gvm.lang()); 
        return gvm.uptodate() ? i18n.__("FirmwareNoNewVersion") : i18n.__("FirmwareNewVersion");
    }, gvm);
    gvm.firmwareStatusStyle = ko.computed(function() {
        return gvm.uptodate() ? "label-success" : "label-warning";
    }, viewModel);
    
    /* Download info text binding and style binding */
    gvm.firmwareDownloadLabel = ko.computed(function(){
        i18n.setLocale(gvm.lang()); 
        return gvm.downloaded() ? i18n.__("FirmwareDownloadedYes") : i18n.__("FirmwareDownloadedNo");
    }, gvm);
    gvm.firmwareDownloadStyle = ko.computed(function() {
        return gvm.downloaded() ? "label-success" : "label-warning";
    }, viewModel);
}

/**
 * Function used as a callback for one the dpt-firmware functions.
 * @param {type} data data received by the dpt-board API.
 */
function updateFirmwareView(data) {
    viewModel.uptodate(data['up-to-date']);
    viewModel.releasedate(data['release-date']);
    viewModel.version(data['version']);
    viewModel.clearChangelist();
    viewModel.downloaded(data['downloaded']);

    $.each(data['changes'], function(index,value){
       viewModel.addFirmwareChange(value); 
    });
    $('#firmware-check-loader').hide();
}

/**
 * Function to update UI while downloading firmware
 */
function downloadPolling() {
    dpt_getFirmwareInfo(function(data){
        updateFirmwareView(data);
        if(!data['downloaded']){
            setTimeout(downloadPolling, 1000); 
        } else {
            $('#firmware-download-loader').hide();
        }
    }, 
    function(){
        alert("Could not check firmware status");
    });
}

/**
 * Called when page is loaded
 */
function initPage() {
    /* Firmware check button click handler */
    $('#checkFirmwareBtn').click(function() {
        $('#firmware-check-loader').show();
        dpt_checkFirmwareUpgrade(function(data) {updateFirmwareView(data);}, function(error) {
            $('#firmware-check-loader').hide();
            alert("Could not check firmware");
        });
    });
    
    /* Firmware download button click handler */
    $('#firmware-download-btn').click(function(){
        $('#firmware-download-loader').show();
        dpt_downloadFirmware(function(data){
            downloadPolling();
        }, function(){
            alert("Could not download firmware");
            $('#firmware-download-loader').hide();
        })
    });
    
    /* Firmware install button click handler */
    $('#firmware-install-btn').click(function(){
        var keepSettings = $('#firmware-keep-settings-chk').prop('checked');
        dpt_installFirmware(keepSettings,
        function(){
            alert(i18n.__("FirmwareInstallStartInfo"));
        },
        function(){
            alert("Could not install firmware");
        })
    });
    
    dpt_getFirmwareInfo(function(data) {updateFirmwareView(data);}, function(error){
        alert("Could not load firmware information");
    });
}