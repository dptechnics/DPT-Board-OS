/* global ko, i18n */

/**
 * The page viewmodel, this is auto-instantiated in global.js
 * @param {Knockout viewmodel} gvm - the global knockout viewmodel
 * @returns {void}
 */
function pageViewModel(gvm) {
    // Page title
    gvm.title = ko.computed(function(){i18n.setLocale(gvm.lang()); return gvm.app() + " - " + i18n.__("BluecherrySettingsTitle");}, gvm);

    // Page i18n 
    gvm.blueCherrySettingsTitle = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BluecherrySettingsTitle");}, gvm);
    gvm.blueCherrySuccess = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherrySuccess");}, gvm);
    gvm.blueCherryConnectInfo = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherryConnectInfo");}, gvm);
    gvm.blueCherryConnectBtn = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherryConnectBtn");}, gvm);
    gvm.blueCherryForgotPassBtn = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherryForgotPassBtn");}, gvm);
    gvm.blueCherryNoAccountBtn = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherryNoAccountBtn");}, gvm);
    gvm.blueCherryYourEmailAddress = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherryYourEmailAddress");}, gvm);
    gvm.blueCherryYourPassword = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherryYourPassword");}, gvm);
    gvm.blueCherryEmailPlaceholder = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherryEmailPlaceholder");}, gvm);
    gvm.blueCherryPasswordPlaceholder = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherryPasswordPlaceholder");}, gvm);
    gvm.blueCherryConnected = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherryConnected");}, gvm);
    gvm.blueCherryNoInternet = ko.computed(function(){i18n.setLocale(gvm.lang()); return i18n.__("BlueCherryNoInternet");}, gvm);
}

/**
 * Called when page is loaded
 */
function initPage() {
    /* Check the current BlueCherry status */
    dpt_blueCherryStatus(function(status){
       switch(status) {
           case BLUECHERRY_NOT_INITIALISED:
               $('#bluecherry_connect').show();
               break;
           case BLUECHERRY_NO_INTERNET:
               $('#bluecherry_status_no_inet').show();
               break;
           case BLUECHERRY_CONNECTED:
               $('#bluecherry_status_connected').show();
               break;
       } 
    }, function(error) {
        BootstrapDialog.alert("Could not load BlueCherry connection status");
    })
    
    /* Attach bluecherry connect handler */
    $('#loginbtn').click(function() {
        $('#login_error').html("");
        $('#loadergif').show();
    
        var username = $('#username').val();
        var password = $('#password').val();
        
        dpt_blueCherryConnect(username, password, function(data){
            $('#loadergif').hide();
            
            switch (data.result) {
                case BLUECHERRY_INIT_SUCCESS:
                    $('#loginform').hide();
                    $('#successholder').show();
                    $('#connectbtns').hide();
                    break;
                case BLUECHERRY_INIT_WRONG_CREDS:
                    $('#login_error').html(i18n.__("BlueCherryInitWrongCreds"));
                    break;
                case BLUECHERRY_INIT_MAX_REACHED:
                    $('#login_error').html(i18n.__("BlueCherryInitMaxReached"));
                    break;
                default:
                    $('#login_error').html(i18n.__("BlueCherryInitUnknownError"));
                    break;
            }
        }, function(){
            $('#loadergif').hide();
            $('#login_error').html(i18n.__("BlueCherryInitUnknownError"));
        });
    });
}