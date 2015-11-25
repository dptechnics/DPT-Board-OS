/* 
 *
 * Copyright 2014 DPTechnics, Daan Pape.
 *
 * This work is licensed under the Creative Commons 
 * Attribution-NonCommercial 4.0 International 
 * License. To view a copy of this license, 
 * visit http://creativecommons.org/licenses/by-nc/4.0/.
 */

/**
 * Show a modal with id 'modal-**'
 * @param {string} name the name '**' of the modal
 * @returns {undefined}
 */
function showModal(name) {
    var modal = $('#modal-' + name);
    
    /* Hide all modals except this one */
    if(modal != null){
        $('.dpt-modal').hide();
        $(modal).show();
        $('#dpt-modal-overlay').show();
    }
}

/**
 * Hide a modal.
 * @returns {undefined}
 */
function hideModal() {
    $('#dpt-modal-overlay').hide();
}

/**
 * Initialize modal handlers
 * @returns {undefined} 
 */
function initModals() {
    // Hide modal when clicked on overlay
    $('#dpt-modal-overlay').click(function(){
        hideModal();
    });
    
    // Prevent hiding the modal when clicked in modal itself
    $('.dpt-modal').click(function(e){
       e.stopPropagation();
    });
}


