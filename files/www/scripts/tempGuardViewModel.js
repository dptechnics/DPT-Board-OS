/**
 * The page viewmodel, gvm is auto-instantiated in global.js
 * @param {Knockout viewmodel} gvm description: the global knockout viewmodel
 * @returns {void}
 */
function pageViewModel(gvm) {
    // Page title
    gvm.title = ko.computed(function(){i18n.setLocale(gvm.lang()); return gvm.app() + " - " + i18n.__("IndexTitle");}, gvm);
}

/**
 * This function is called after system initalisation and will
 * be called on a regular basis.
 * @callback {function} call with true or false, on false polling will stop
 * @returns {void}
 */
function updateInfo(callback) {
	$('#statusrefresh').removeClass("btn-success");
	$('#statusrefresh').addClass("btn-warning");
	$.get("/api/tempsensor/read", function(data) {
		$('#statusrefresh').addClass("btn-success");
		$('#statusrefresh').removeClass("btn-warning");
		$('#temp').html(data.temperature);
		callback(true);
	});
}