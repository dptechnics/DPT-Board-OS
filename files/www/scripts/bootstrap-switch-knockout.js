/**
 * Knockout binding handler for bootstrapSwitch indicating the status
 * of the switch (on/off): https://github.com/nostalgiaz/bootstrap-switch
 */
ko.bindingHandlers.bootstrapSwitchOn = {
    init: function (element, valueAccessor, allBindingsAccessor, viewModel) {
        $elem = $(element);
        $(element).bootstrapSwitch();
        $(element).bootstrapSwitch('setState', ko.utils.unwrapObservable(valueAccessor()));
    },
    update: function (element, valueAccessor, allBindingsAccessor, viewModel) {
        var vStatus = $(element).bootstrapSwitch('state');
        var vmStatus = ko.utils.unwrapObservable(valueAccessor());
        if (vStatus != vmStatus) {
            /* Skip updates from triggering the handler */
            $(element).bootstrapSwitch('setState', vmStatus, true);
        }
    }
};