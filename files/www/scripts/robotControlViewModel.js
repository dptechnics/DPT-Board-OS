/**
 * The page viewmodel, gvm is auto-instantiated in global.js
 * @param {Knockout viewmodel} gvm description: the global knockout viewmodel
 * @returns {void}
 */
function pageViewModel(gvm) {
    // Page title
    gvm.title = ko.computed(function(){i18n.setLocale(gvm.lang()); return this.app() + " - " + i18n.__("RobotcontrolTitle");}, gvm);
}

/**
 * Automatically called page initialisation.
 * @returns {void}
 */
function initPage() {
    $('#btn-forward').on('touchstart mousedown',function(){
        dptr_moveForward();
    });

    $('#btn-forward').on('touchend mouseup',function(){
        dptr_stopMotor();
    });

    $('#btn-backward').on('touchstart mousedown',function(){
        dptr_moveBackward();
    });

    $('#btn-backward').on('touchend mouseup',function(){
        dptr_stopMotor();
    });

    $('#btn-left').on('touchstart mousedown',function(){
        dptr_moveLeft();
    });

    $('#btn-left').on('touchend mouseup',function(){
        dptr_stopMotor();
    });

    $('#btn-right').on('touchstart mousedown',function(){
        dptr_moveRight();
    });

    $('#btn-right').on('touchend mouseup',function(){
        dptr_stopMotor();
    });
}