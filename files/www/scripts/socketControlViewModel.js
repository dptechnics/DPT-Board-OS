/**
 * The page viewmodel, gvm is auto-instantiated in global.js
 * @param {Knockout viewmodel} gvm description: the global knockout viewmodel
 * @returns {void}
 */
function pageViewModel(gvm) {
    // Page title
    gvm.title = ko.computed(function(){i18n.setLocale(gvm.lang()); return gvm.app() + " - " + i18n.__("ButtoncontrolTitle");}, gvm);
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
 * Automatically called page initialisation.
 * @returns {void}
 */
function initPage() {
    $('#switch-a').bootstrapSwitch();
    $('#switch-b').bootstrapSwitch();
    $('#switch-c').bootstrapSwitch();
    
    $('#switch-a').bind('switch-change', function(event, data){
            $.ajax({
		type: "PUT",
		contentType: "application/json; charset=utf-8",
		url: DPT_AJAX_PREFIX + '/api/443mhz/' + (data.value ? 'A' : 'a'),
		dataType: "json"
            });
        });
        
        $('#switch-b').bind('switch-change', function(event, data){
            $.ajax({
		type: "PUT",
		contentType: "application/json; charset=utf-8",
		url: DPT_AJAX_PREFIX + '/api/443mhz/' + (data.value ? 'A' : 'a'),
		dataType: "json"
            });
        });
        
        $('#switch-c').bind('switch-change', function(event, data){       
            $.ajax({
		type: "PUT",
		contentType: "application/json; charset=utf-8",
		url: DPT_AJAX_PREFIX + '/api/443mhz/' + (data.value ? 'C' : 'c'),
		dataType: "json"
            });
        });
}