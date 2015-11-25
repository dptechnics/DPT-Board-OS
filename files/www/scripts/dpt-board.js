/*
 * DPT-Board javascript library version 0.1
 * (c) 2014 DPTechnics
 * Author: Daan Pape
 *
 * Requires: JQuery
 */
 
/* Ajax prefix, mostly used for development */
var DPT_AJAX_PREFIX = "/";

/* WiFi security types */
var WIFI_SECURITY_NONE                  = 0;
var WIFI_SECURITY_WEP                   = 1;
var WIFI_SECURITY_WPA_PERSONAL          = 2;
var WIFI_SECURITY_WPA2_PERSONAL         = 3;
var WIFI_SECURITY_WPA_ENTERPRISE        = 4;
var WIFI_SECURITY_WPA2_ENTERPRISE       = 5;

/* WiFi networks */
var WIFI_BOARD_NETWORK                  = 1;
var WIFI_CLIENT_NETWORK                 = 2;

/* WiFi status results */
var WIFI_STATUS_OK                      = 200;
var WIFI_ERROR_UNKNOWN_ERROR            = 100;
var WIFI_ERROR_BAD_NETWORK_DESCRIPTOR   = 101;
var WIFI_ERROR_SSID_TO_LONG             = 102;
var WIFI_ERROR_NO_RESTART               = 103;

/* BlueCherry status codes */
var BLUECHERRY_NOT_INITIALISED          = 1;
var BLUECHERRY_NO_INTERNET              = 2;
var BLUECHERRY_CONNECTED                = 3;

/* BlueCherry init status codes */
var BLUECHERRY_INIT_SUCCESS             = 0;
var BLUECHERRY_INIT_MAX_REACHED         = 1;
var BLUECHERRY_INIT_WRONG_CREDS         = 2;
var BLUECHERRY_INIT_ERR_UNKNOWN         = 3;

/* GPIO modes */ 
var GPIO_ACT_LOW =  0;               				/* Use GPIO as active low mode */
var GPIO_ACT_HIGH = 1 ;            				/* Use GPIO as active high mode */   

/**
 * Get general system information.
 * @param {function} callback function to call when data is ready.
 * @param {function} errorhandler function to call when an error occurs.
 * @returns {undefined}
 */
function dpt_getSystemOverview(callback, errorhandler)
{
    $.getJSON(DPT_AJAX_PREFIX + 'api/system/overview', callback).error(errorhandler);
}

/**
 * Get the currently available IO ports in the system.
 * @param {function} callback function to call when data is ready.
 * @param {function} errorhandler function to call when an error occurs.
 * @returns {undefined}
 */
function dpt_getIOLayout(callback, errorhandler)
{
    $.getJSON(DPT_AJAX_PREFIX + 'api/gpio/layout', function(data){
        // call the function with the number of ports and portlist
        callback(data.ioports.length, data.ioports);
    }).error(errorhandler);
}

/**
 * Get the currently available IO ports and their status in the system. 
 * @param {type} callback function to call when data is ready.
 * @param {type} errorhandler function to call when an error occurs.
 * @returns {undefined}
 */
function dpt_getIOOverview(callback, errorhandler)
{
    $.getJSON(DPT_AJAX_PREFIX + 'api/gpio/overview', function(data){
        // call the function with the number of ports and portlist
        callback(data.ports.length, data.ports);
    }).error(errorhandler);
}

/**
 * Toggle an IO pin on the board 
 * @param {integer} name the name of the IO pin, only the number.
 * @param {function} errorhandler function to call when an error occurs.
 * @returns {undefined}
 */
function dpt_toggleIO(name, errorhandler)
{
    // Get the current pin state 
    $.getJSON(DPT_AJAX_PREFIX + 'api/gpio/state/' + name, function(data) {
        // Toggle the pin
        $.ajax({
            type: "PUT",
            contentType: "application/json; charset=utf-8",
            url: DPT_AJAX_PREFIX + 'api/gpio/state/' + name + '/' + (data.state === 0 ? 1 : 0),
            dataType: "json",
            error: errorhandler
        });
    }).error(errorhandler);
}

/**
 * Get the state of an IO pin. 
 * @param {integer} name the name of the IO pin, only the number.
 * @param {function} callback called with the result.
 * @param {function} errorhandler function to call when an error occurs.
 */
function dpt_getIO(name, callback, errorhandler)
{
	$.getJSON(DPT_AJAX_PREFIX + 'api/gpio/state/' + name, function(data) {
		callback(data.state === 1);
    }).error(errorhandler);
}

/**
 * Set an IO pin on the board to a predefined state.
 * @param {integer} name the name of the IO pin, only the number.
 * @param {boolean} state the new state of the IO pin, boolean.
 * @param {function} errorhandler function to call when an error occurs.
 * @returns {undefined} 
 */
function dpt_setIO(name, state, errorhandler)
{
    $.ajax({
        type: "PUT",
        contentType: "application/json; charset=utf-8",
        url: DPT_AJAX_PREFIX + 'api/gpio/state/' + name + '/' + (state ? 1 : 0),
        dataType: "json",
        error: errorhandler
    });
}

/**
 * Set an IO pin on the board to a predefined state.
 * @param {integer} name the name of the IO pin, only the number.
 * @param {integer} the type of pulse to give.
 * @param {integer} type the length to pulse.
 * @param {function} errorhandler function to call when an error occurs.
 * @returns {undefined} 
 */
function dpt_pulseIO(name, mode, time, errorhandler)
{
    $.ajax({
        type: "PUT",
        contentType: "application/json; charset=utf-8",
        url: DPT_AJAX_PREFIX + 'api/gpio/pulse/' + name + '/' + mode + '/' + time,
        dataType: "json",
        error: errorhandler
    });
}

/**
 * Scan for available WiFi networks and get information on the encryption and strength.
 * @param {function} callback function to call when data is ready.
 * @param {function} errorhandler function to call when an error occurs.
 * @returns {undefined} 
 */
function dpt_getWifiScan(callback, errorhandler)
{
    $.getJSON(DPT_AJAX_PREFIX + 'api/wifi/scan', function(data) {
        callback(data);
    }).error(errorhandler);
}

/**
 * Request the DPT-Board to perform a WiFi scan. 
 * @param {type} callback function to call when scanning was successful.
 * @param {type} errorhandler function to call when an error occurs. 
 * @returns {undefined} 
 */
function dpt_requestWiFiScan(callback, errorhandler)
{
    $.getJSON(DPT_AJAX_PREFIX + 'api/wifi/requestscan', function(data) {
        if(data.result !== WIFI_STATUS_OK) {
            errorhandler(data.result);
        } else {
            callback(data);
        }
    }).error(errorhandler);
}

/**
 * Get information about the current WiFi network status of all networks. 
 * @param {type} callback function to call when data is ready. 
 * @param {type} errorhandler function to call when an error occurs. 
 * @returns {undefined} 
 */
function dpt_getWifiStatus(callback, errorhandler)
{
    $.getJSON(DPT_AJAX_PREFIX + 'api/wifi/info', function(data) {
        callback(data);
    }).error(errorhandler);
}

/**
 * Set the status of a WiFi network to enabled or disabled. 
 * @param {type} network the network to set the status for.
 * @param {type} status the new status to apply. 
 * @param {type} callback the callback after success. 
 * @param {type} errorhandler the errorhandler. 
 * @returns {undefined}
 */
function dpt_setWiFiStatus(network, status, callback, errorhandler)
{
    $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        url: DPT_AJAX_PREFIX + 'api/wifi/setstate',
        data: JSON.stringify({
            network : network,
            state : status
        }),
        dataType: "json",
        success: callback,
        error: errorhandler
    });
}

/**
 * Set the network settings for the DPT-Board WiFi network
 * @param {type} ssid the new SSID
 * @param {type} status the new status (enabled or disabled)
 * @param {type} callback the callback after success.
 * @param {type} errorhandler the errorhandler.
 * @returns {undefined}
 */
function dpt_setBoardNetworkSettings(ssid, status, callback, errorhandler)
{
    $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        url: DPT_AJAX_PREFIX + 'api/wifi/setsimplesettings',
        data: JSON.stringify({
            network : WIFI_BOARD_NETWORK,
            ssid : ssid,
            state : status
        }),
        dataType: "json",
        success: callback,
        error: errorhandler
    });
}

/**
 * Make the DPT-Board connect to a WiFi network. When te connection fails as 
 * a cause of bad credentials the WiFi connection will be dropped and come
 * back within 1 minute. 
 * @param {type} ssid the SSID to connect to.
 * @param {type} enctype the used encryption type.
 * @param {type} username the username 
 * @param {type} password
 * @param {type} callback
 * @param {type} errorhandler
 * @returns {undefined}
 */
function dpt_clientWiFiConnect(ssid, enctype, username, password, callback, errorhandler)
{
    $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        url: DPT_AJAX_PREFIX + 'api/wifi/connect',
        data: JSON.stringify({
            ssid : ssid,
            security : enctype,
            password : password,
            username : username
        }),
        dataType: "json",
        success: callback,
        error: errorhandler
    });
}

/**
 * Get information about the current board firmware status
 * @param {function} callback function to call when data is ready.
 * @param {function} errorhandler function to call when an error occurs.
 * @returns {undefined}
 */
function dpt_getFirmwareInfo(callback, errorhandler)
{
    $.getJSON(DPT_AJAX_PREFIX + 'api/firmware/info', function(data) {
        callback(data);
    }).error(errorhandler);
}

/**
 * Get information about the current board firmware status but only
 * after check with the dptechnics servers. 
 * @param {function} callback function to call when data is ready.
 * @param {function} errorhandler function to call when an error occurs.
 * @returns {undefined}
 */
function dpt_checkFirmwareUpgrade(callback, errorhandler)
{
    $.getJSON(DPT_AJAX_PREFIX + 'api/firmware/check', function(data) {
        dpt_getFirmwareInfo(callback, errorhandler);
    }).error(errorhandler);
}

/**
 * Download the latest available firmware file to disk.
 * @param {type} callback called on success.
 * @param {type} errorhandler called on error.
 */
function dpt_downloadFirmware(callback, errorhandler)
{
    $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        url: DPT_AJAX_PREFIX + 'api/firmware/download',
        dataType: "json",
        success: callback,
        error: errorhandler
    });
}

/**
 * Install the downloaded firmware file on the board.
 * @param {boolean} keepSettings when true user settings will be saved.
 * @param {type} callback called on success.
 * @param {type} errorhandler called on error.
 */
function dpt_installFirmware(keepSettings, callback, errorhandler)
{
    $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        url: DPT_AJAX_PREFIX + 'api/firmware/install',
        data: JSON.stringify({keep_settings : keepSettings}),
        dataType: "json",
        success: callback,
        error: errorhandler
    });
}

/**
 * Connect this board to the BlueCherry service. 
 * @param {type} username
 * @param {type} password
 * @param {type} callback
 * @param {type} errorhandler
 * @returns {undefined}
 */
function dpt_blueCherryConnect(username, password, callback, errorhandler)
{
    $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        url: DPT_AJAX_PREFIX + 'api/bluecherry/init',
        data: JSON.stringify({username : username, password: password}),
        dataType: "json",
        success: callback,
        error: errorhandler
    });
}

/**
 * Get the status of 
 * @param {type} callback
 * @param {type} errorhandler
 * @returns {undefined}
 */
function dpt_blueCherryStatus(callback, errorhandler)
{
    $.getJSON(DPT_AJAX_PREFIX + 'api/bluecherry/status', function(data) {
        callback(data.status);
    }).error(errorhandler);
}
