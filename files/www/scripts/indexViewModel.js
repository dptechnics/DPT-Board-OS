/**
 * The page viewmodel, gvm is auto-instantiated in global.js
 * @param {Knockout viewmodel} gvm description: the global knockout viewmodel
 * @returns {void}
 */
function pageViewModel(gvm) {
    // Page title
    gvm.title = ko.computed(function(){i18n.setLocale(gvm.lang()); return gvm.app() + " - " + i18n.__("IndexTitle");}, gvm);

    // I18N bindings
    gvm.systemTitle = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("System");}, gvm);
    gvm.storageTitle = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("Storage");}, gvm);
    gvm.neworkTitle = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("Network");}, gvm);
        
    gvm.overviewSysName = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("OverviewSysName");}, gvm);
    gvm.overviewBoardModel = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("OverviewBoardModel");}, gvm);
    gvm.overviewBoardStatus = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("OverviewBoardStatus");}, gvm);
    gvm.networkPort1 = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("NetworkPort1");}, gvm);
    gvm.networkPort2 = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("NetworkPort2");}, gvm);
    gvm.networkWiFiState = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("NeworkWiFiState");}, gvm);
    gvm.storageState = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("StorageState");}, gvm);
    gvm.storageSpace = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("StorageSpace");}, gvm);
    gvm.systemLoadStatus = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("SystemLoad");}, gvm);
    gvm.ramUsageStatus = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("RamUsage");}, gvm);

    gvm.stateOk = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("StateOk");}, gvm);
    gvm.stateConnected = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("StateConnected");}, gvm);
    gvm.stateNotConnected = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("StateNotConnected");}, gvm);
    gvm.stateInstalled = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("StateInstalled");}, gvm);
    gvm.stateNotInstalled = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("StateNotInstalled");}, gvm);

    // Data bindings observable
    gvm.freeStorage = ko.observable(0);
    gvm.totalStorage = ko.observable(0);
    gvm.dataSysName = ko.observable("");
    gvm.dataModelName = ko.observable("");
    gvm.dataConnStateOne = ko.observable(false);
    gvm.dataConnStateTwo = ko.observable(false);
    gvm.dataUSBStor = ko.observable("");
    gvm.dataSystemLoad = ko.observable("");
    gvm.totalRAM = ko.observable(0);
    gvm.freeRAM = ko.observable(0);

    // Data bindings computed 
    gvm.storageMessage = ko.computed(function(){
        return (gvm.totalStorage() - gvm.freeStorage()) + "/" + gvm.totalStorage() + " Mb";
    }, gvm);

    gvm.ramMessage = ko.computed(function(){
        freeRamMiB = Math.round((gvm.freeRAM()/10.24)/100);
        totalRamMiB = Math.round((gvm.totalRAM()/10.24)/100);
        return (totalRamMiB - freeRamMiB) + "/" + totalRamMiB + " Mb";
    },gvm);

    gvm.textConnStateOne = ko.computed(function(){
        i18n.setLocale(gvm.lang());
        return gvm.dataConnStateOne() ? i18n.__("StateConnected") : i18n.__("StateNotConnected");
    }, gvm);

    gvm.textConnStateTwo = ko.computed(function(){
        i18n.setLocale(gvm.lang());
        return gvm.dataConnStateTwo() ? i18n.__("StateConnected") : i18n.__("StateNotConnected");
    }, gvm);

    gvm.textUSBStor = ko.computed(function(){
        i18n.setLocale(gvm.lang());
        switch(gvm.dataUSBStor()){
            case "mounted":
                return i18n.__("StateInstalledAndMounted");
            case "notmounted":
                return i18n.__("StateInstalledNotMounted");
            case "notinstalled":
                return i18n.__("StateNotInstalled");
        }
    }, gvm);

    // Style bindings
    gvm.style_storageWidth = ko.computed(function(){
        return ((gvm.totalStorage() - gvm.freeStorage())/gvm.totalStorage())*100;
    }, gvm);

    gvm.styleConnStateOne = ko.computed(function(){
        return gvm.dataConnStateOne() ? "label-success" : "label-default";
    }, gvm);

    gvm.styleConnStateTwo = ko.computed(function(){
        return gvm.dataConnStateTwo() ? "label-success" : "label-default";
    }, gvm);

    gvm.styleUSBStor = ko.computed(function(){
        switch(gvm.dataUSBStor()){
            case "mounted":
                    return "label-success";
            case "notmounted":
                    return "label-info";
            case "notinstalled":
                    return "label-default";
        }
    }, gvm);
    
    gvm.style_ramWidth = ko.computed(function(){
        return ((gvm.totalRAM() - gvm.freeRAM())/gvm.totalRAM())*100;
    }, gvm);

    /**
     * Set the board USB disk space
     * @param {integer} free - the free disk space
     * @param {integer} total - the total disk space
     * @returns {void}
     */
    gvm.setDiskSpace = function(free, total) {
        gvm.freeStorage(free);
        gvm.totalStorage(total);
    }

    /**
     * Set the board disk connection state
     * @param {string} state - the USB disk connection state
     * @returns {void}
     */
    gvm.setDiskState = function(state) {
        gvm.dataUSBStor(state);
    }

    /**
     * Set the board connection state
     * @param {boolean} port1 - connection state of port 1
     * @param {boolean} port2 - connection state of port 2
     * @returns {void}
     */
    gvm.setConnectionState = function(port1, port2) {
        gvm.dataConnStateOne(port1);
        gvm.dataConnStateTwo(port2);
    }

    /**
     * Set board information
     * @param {string} name - the system name 
     * @param {string} model - the board model
     * @returns {void}
     */
    gvm.setBoardInfo = function(name, model) {
        gvm.dataSysName(name);
        gvm.dataModelName(model);
    }

    /**
     * Update system statistics
     * @param {string} load - the system load
     * @param {integer} totalram - the total RAM in system
     * @param {integer} freeram - the free RAM in system
     * @returns {void}
     */
    gvm.setSystemInfo = function(load, totalram, freeram) {
        gvm.dataSystemLoad(load);
        gvm.totalRAM(totalram);
        gvm.freeRAM(freeram);
    }
}

/**
 * This function is called after system initalisation and will
 * be called on a regular basis.
 * @callback {function} call with true or false, on false polling will stop
 * @returns {void}
 */
function updateInfo(callback) {
    dpt_getSystemOverview(function(data) {
        // Update the view 
        viewModel.setBoardInfo(data.sysname, data.model);
        viewModel.setConnectionState(data.eth0_connected, data.eth1_connected);
        viewModel.setDiskState(data.usb_state);
        viewModel.setDiskSpace(data.usb_free, data.usb_total);
        viewModel.setSystemInfo(data.system_load, data.ram_total, data.ram_free);
        
        // Polling success
        callback(true);
    }, function(error) {
        callback(false);
    });
}