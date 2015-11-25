/* global ko, i18n, viewModel */

/**
 * The page viewmodel, this is auto-instantiated in global.js
 * @param {Knockout viewmodel} gvm - the global knockout viewmodel
 * @returns {void}
 */
function pageViewModel(gvm) {
    // Page title
    gvm.title = ko.computed(function(){i18n.setLocale(gvm.lang()); return gvm.app() + " - " + i18n.__("WiFiSettingsTitle");}, gvm);

    // Page data 
    gvm.WiFiStatus = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("WiFiStatus");}, gvm);
    gvm.WiFiSSID = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("WiFiSSID");}, gvm);
    gvm.WiFiSignalStrength = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("WifiSignalStrength");}, gvm);
    gvm.boardWiFiConnection = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("WiFiBoardConnection");}, gvm);
    gvm.clientWiFiConnection = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("WiFiClientConnection");}, gvm);
    gvm.wifiAvailableNetworks = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("wifiAvailableNetworks");}, gvm);
    gvm.wifiSecurity = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("WiFiSecurity");}, gvm);
    gvm.editSettingsBtn = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("EditSettings");}, gvm);
    
    // Data bindings 
    gvm.boardWiFiSSID = ko.observable("");
    gvm.clientWiFiSSID = ko.observable("");
    gvm.clientWiFiStrength = ko.observable(0);
    gvm.wifiNetworks = ko.observableArray([]);
    gvm.boardConnState = ko.observable(false);
    gvm.clientEnState = ko.observable(false);
    gvm.clientConnState = ko.observable(false);
    
    gvm.textBoardWiFiState = ko.computed(function(){
        i18n.setLocale(gvm.lang());
        return gvm.boardConnState() ? i18n.__("StateEnabled") : i18n.__("StateDisabled");
    }, gvm);

    gvm.textClientWifiState = ko.computed(function(){
        i18n.setLocale(gvm.lang());
        return gvm.clientConnState() ? i18n.__("StateConnected") : i18n.__("StateNotConnected");
    }, gvm);

    // Style bindings
    gvm.styleBoardWiFiState = ko.computed(function(){
        return gvm.boardConnState() ? "label-success" : "label-default";
    }, gvm);
    
    gvm.styleClientWiFiState = ko.computed(function(){
        return gvm.clientConnState() ? "label-success" : "label-default";
    }, gvm);
    
    /*
     * Update the WiFi networks information
     */
    gvm.updateWifiInfo = function(data) {        
        for(var i in data) {
            var wifi = data[i];
            if(wifi.network === "config") {      
                // This is the board WiFi connection
                gvm.boardWiFiSSID(wifi.SSID);
                gvm.boardConnState(wifi.enabled);
            } else {
                gvm.clientEnState(wifi.enabled);
                gvm.clientConnState(wifi.connected);
                gvm.clientWiFiStrength(wifi.quality < 0 ? 0 : wifi.quality);
                gvm.clientWiFiSSID(wifi.SSID);
            }
        }
    };
    
    /*
     * Update the location dropdown list
     */
    gvm.updateWiFiNetworks = function(data) {
        if(data.result === 'done') {
            // Clear the current list
            gvm.wifiNetworks.destroyAll();
            
            // Show best quality WiFi networks first
            sortJsonResult(data.networks, 'quality', false);

            $.each(data.networks, function(i, item){
                var sec = item.secured ? '-sec' : '';

                // Get wifi strength class from quality 
                if(item.quality >= 75) {
                    item.iconclass = 'wifi-strength' + sec + '-high';
                } else if (item.quality >= 50) {
                    item.iconclass = 'wifi-strength' + sec + '-medhigh';
                } else if (item.quality >= 25) {
                    item.iconclass = 'wifi-strength' + sec + '-medlow';
                } else {
                    item.iconclass = 'wifi-strength' + sec + '-low';
                }
                
                /* Add i18n text */
                item.wifiSecurity = gvm.wifiSecurity;

                // Add the network to the array
                gvm.wifiNetworks.push(item);
            });
        }
    };
}

/**
 * This function is called after system initalisation and will
 * be called on a regular basis.
 * @param {function} callback {function} call with true or false, on false polling will stop
 * @returns {void}
 */
function updateInfo(callback) {
    dpt_getWifiScan(function(data) {
        viewModel.updateWiFiNetworks(data); 
        //callback(true);
        dpt_getWifiStatus(function(info){
            viewModel.updateWifiInfo(info);
            callback(true);
        }, function(){
            callback(true);
        });
    }, function(){
        console.log("Could not fetch WiFi scan information");
        callback(true);
    });
}

/**
 * Start scanning for WiFi networks
 * @returns {undefined}
 */
function startWiFiScanRequests() {
    dpt_requestWiFiScan(function(){
        setTimeout(function(){startWiFiScanRequests();}, 5000);
    }, function(){
        setTimeout(function(){startWiFiScanRequests();}, 5000);
    });
}

/**
 * Initialize page
 * @returns {undefined}
 */
function initPage() {
    /* Start scanning for WiFi networks */
    startWiFiScanRequests();
    
    // Bind to the board WiFi settings change button
    $('#editBoardWiFiSettingsBtn').click(function() {
        BootstrapDialog.show({
            title: i18n.__("ModalBoardWiFiSettingsChangeTitle"),
            message: $('<div></div>').load("modals/wifi-modal-settings.html"),
            buttons: [{
                label: i18n.__("BtnCancel"),
                action: function(dialog) {
                    dialog.close();
                }
            },{
                label: i18n.__("BtnSave"),
                action: function(dialog) {
                    var modalssid = $('#modal_wifissid').val();
                    var modalstate = $('#modal_wifistatus').bootstrapSwitch('state');
                    
                    dialog.close();
                    // If one of the settings is different apply
                    if(modalssid !== viewModel.boardWiFiSSID()) {
                        // SSID changed, check state
                        if(modalstate !== viewModel.boardConnState()) {
                            if(modalstate === false) {
                                // The state has changed to off, show yes/no question
                                BootstrapDialog.show({
                                    title: i18n.__("ModalTitleAreYouSure"), 
                                    message: i18n.__("ModalBoardWiFiTurnOff"),
                                    buttons: [
                                        {
                                            label: i18n.__("BtnNo"),
                                            action: function(d){
                                                d.close();
                                            }
                                        }, {
                                            label: i18n.__("BtnYes"),
                                            action: function(d) {
                                                d.close();
                                                // Turn off the board WiFi and set the new SSID
                                                dpt_setBoardNetworkSettings(modalssid, false, function(){}, function(){
                                                    BootstrapDialog.alert(i18n.__("ModalWifiSettingsError"));
                                                });
                                            }
                                        }
                                    ]
                                });
                            } else {
                                // The state has changed to on, set state and SSID
                                BootstrapDialog.show({
                                    title: i18n.__("ModalTitleAreYouSure"), 
                                    message: i18n.__("ModalClientSaveSettings"),
                                    buttons: [
                                        {
                                            label: i18n.__("BtnNo"),
                                            action: function(d){
                                                d.close();
                                            }
                                        }, {
                                            label: i18n.__("BtnYes"),
                                            action: function(d) {
                                                d.close();
                                                // Turn off the board WiFi and set the new SSID
                                                dpt_setBoardNetworkSettings(modalssid, true, function(){
                                                    BootstrapDialog.alert(i18n.__("ModalWiFiBoardWiFiSwitchedOn"));
                                                }, function(){
                                                    BootstrapDialog.alert(i18n.__("ModalWifiSettingsError"));
                                                });
                                            }
                                        }
                                    ]
                                });
                            }
                        } else {
                            // network state not changed, only set SSID
                            BootstrapDialog.show({
                                title: i18n.__("ModalTitleAreYouSure"), 
                                message: i18n.__("ModalClientSaveSettings"),
                                buttons: [
                                    {
                                        label: i18n.__("BtnNo"),
                                        action: function(d){
                                            d.close();
                                        }
                                    }, {
                                        label: i18n.__("BtnYes"),
                                        action: function(d) {
                                            d.close();
                                            // Turn off the board WiFi and set the new SSID
                                            dpt_setBoardNetworkSettings(modalssid, modalstate, function(){ }, function(){
                                                BootstrapDialog.alert(i18n.__("ModalWifiSettingsError"));
                                            });
                                        }
                                    }
                                ]
                            });
                        }
                    } else {
                        // SSID not changed, check state
                        if($('#modal_wifistatus').bootstrapSwitch('state') !== viewModel.boardConnState()) {
                            if($('#modal_wifistatus').bootstrapSwitch('state') === false) {
                                // The state has changed to off, show yes/no question
                                BootstrapDialog.show({
                                    title: i18n.__("ModalTitleAreYouSure"), 
                                    message: i18n.__("ModalBoardWiFiTurnOff"),
                                    buttons: [
                                        {
                                            label: i18n.__("BtnNo"),
                                            action: function(d){
                                                d.close();
                                            }
                                        }, {
                                            label: i18n.__("BtnYes"),
                                            action: function(d) {
                                                // Turn off the board WiFi
                                                dpt_setWiFiStatus(WIFI_BOARD_NETWORK, false, function(){}, function(){
                                                    BootstrapDialog.alert(i18n.__("ModalWifiSettingsError"));
                                                });
                                                d.close();
                                            }
                                        }
                                    ]
                                });
                            } else {
                                // Turn on the board WiFi
                                dpt_setWiFiStatus(WIFI_BOARD_NETWORK, true, function(){
                                    BootstrapDialog.alert(i18n.__("ModalWiFiBoardWiFiSwitchedOn"));
                                }, function(){
                                    BootstrapDialog.alert(i18n.__("ModalWifiSettingsError"));
                                });
                            }
                        }
                    }
                }
            }],
            onshown : function() {
                $('#modal_wifistatuslabel').html(viewModel.WiFiStatus());
                $('#modal_wifinamelabel').html(viewModel.WiFiSSID());
                $('#modal_wifistatus').bootstrapSwitch();
                $('#modal_wifistatus').bootstrapSwitch('setState', viewModel.boardConnState());
                $('#modal_wifissid').val(viewModel.boardWiFiSSID());
            }
        });
    });
    
    // Bind to the client WiFi status button
    $('#clientWiFiBtn').bind('switch-change', function(event, data){
        if(viewModel.clientConnState() !== data.value){
            if(data.value === true) {
                dpt_setWiFiStatus(WIFI_CLIENT_NETWORK, true, function(){
                    BootstrapDialog.alert(i18n.__("ModalWiFiClientWiFiSwitchedOn"));
                }, function(){
                    dialog.close();
                    BootstrapDialog.alert(i18n.__("ModalWifiSettingsError"));
                });
            } else {
                BootstrapDialog.show({
                    title: i18n.__("ModalBoardWiFiSettingsChangeTitle"),
                    message: i18n.__("ModalClientSaveSettings"),
                    buttons: [{
                        label: i18n.__("BtnCancel"),
                        action: function(dialog) {
                            $('#clientWiFiBtn').bootstrapSwitch("setState", true);
                            dialog.close();
                        }
                    },{
                        label: i18n.__("BtnOk"),
                        action: function(dialog) {
                            // Apply settings
                            dpt_setWiFiStatus(WIFI_CLIENT_NETWORK, false, function(){
                                dialog.close();
                            }, function(){
                                dialog.close();
                                BootstrapDialog.alert(i18n.__("ModalWifiSettingsError"));
                            });
                        }
                    }]
                });
            }
        }
    });
}

/**
 * Sorting function based on: http://stackoverflow.com/questions/881510/jquery-sorting-json-by-values
 * @param {type} json the json array of json objects to sort
 * @param {type} fieldname the fieldname in the object you want to sort.
 * @param {type} asc true for ascending
 * @returns {undefined}
 */
function sortJsonResult(json, fieldname, asc) {
    json = json.sort(function(a, b){
        if (asc) 
            return (a[fieldname] > b[fieldname]);
        else 
            return (b[fieldname] > a[fieldname]);
    });
}

/**
 * Show a modal where the user can enter WiFi information and connect to the network. 
 * @param {type} networkdata WiFi network information.
 */
function showConnectionModal(networkdata) {
    // Determine type of modal 
    var modal = "modals/wifi-modal-personal.html";
    switch (networkdata.sec_type) {
        case WIFI_SECURITY_NONE:
            modal = "modals/wifi-modal-unsec.html";
            break;
        case WIFI_SECURITY_WEP:
        case WIFI_SECURITY_WPA_PERSONAL:
        case WIFI_SECURITY_WPA2_PERSONAL:
            modal = "modals/wifi-modal-personal.html";
            break;
        case WIFI_SECURITY_WPA_ENTERPRISE:
        case WIFI_SECURITY_WPA2_ENTERPRISE:
            modal = "modals/wifi-modal-enterprise.html"
            break;
    }
    
    BootstrapDialog.show({
        title: i18n.__("ModalWiFiTitle") + " " + networkdata.ssid,
        message: $('<div></div>').load(modal),
        buttons: [{
            label: i18n.__("BtnCancel"),
            action: function(dialog) {
                dialog.close();
            }
        }, {
            label: i18n.__("BtnConnect"),
            action: function(dialog) {
                // Connect to the WiFi network 
                switch(networkdata.sec_type) {
                    case WIFI_SECURITY_NONE:
                            dpt_clientWiFiConnect(
                                networkdata.ssid, 
                                networkdata.sec_type,
                                "",
                                "",
                                function(data) {
                                    dialog.close();
                                    BootstrapDialog.show({
                                       title: i18n.__("ModalWiFiConnecting") + " " + networkdata.ssid,
                                       message: i18n.__("ModalWiFiClientConnectMsg"),
                                       buttons: [{
                                            label: i18n.__("BtnOk"),
                                            action: function(dialog) {
                                                dialog.close();
                                            }
                                        }]
                                    });
                                },
                                function(data) {
                                    alert("Could not connect to network!");
                                }
                            );
                        break;
                    case WIFI_SECURITY_WPA_PERSONAL:
                    case WIFI_SECURITY_WPA2_PERSONAL:
                        var password = $('#wifi-pass').val();
                        dpt_clientWiFiConnect(
                                networkdata.ssid, 
                                networkdata.sec_type,
                                "",
                                password,
                                function(data) {
                                    dialog.close();
                                    BootstrapDialog.show({
                                       title: i18n.__("ModalWiFiConnecting") + " " + networkdata.ssid,
                                       message: i18n.__("ModalWiFiClientConnectMsg"),
                                       buttons: [{
                                            label: i18n.__("BtnOk"),
                                            action: function(dialog) {
                                                dialog.close();
                                            }
                                        }]
                                    });
                                },
                                function(data) {
                                    BootstrapDialog.alert("Could not connect to the selected WiFi network");
                                }
                            );
                        break;
                    case WIFI_SECURITY_WPA_ENTERPRISE:
                    case WIFI_SECURITY_WPA2_ENTERPRISE:
                        break;
                }
            }
        }]
    });
}