/**
 * The page viewmodel, this is auto-instantiated in global.js
 * @param {Knockout viewmodel} gvm - the global knockout viewmodel
 * @returns {void}
 */
function pageViewModel(gvm) {
    // Page title
    gvm.title = ko.computed(function(){i18n.setLocale(gvm.lang()); return this.app() + " - " + i18n.__("GraphcontrolTitle");}, gvm);
}

/**
 * Automatically called page initialisation.
 * @returns {void}
 */
function initPage(){
    
    // Install SVG button handlers
    $('#io7').click(function(){
        dpt_toggleIO("7");
    });

    $('#io6').click(function(){
        dpt_toggleIO("6");
    });
}