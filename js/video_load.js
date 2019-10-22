
/* Video Image Switcher */
(function ($) {
  Drupal.behaviors.kued_data = {
    attach:function(context, settings) {

    alert(Drupal.settings.kued_data.key);
      var hash = Drupal.settings.kued_data.key;
      $('.'+hash).click(function() {
          $('iframe#'+hash).attr('src', function() {
              return $(this).data('src');
          });
          
          $('.'+hash).hide();
      });
  
      $('iframe#'+hash).each(function() {
          var src = $(this).attr('src');
          $(this).data('src', src).attr('src', '');
      });

/*
// Kept for reference
  var iframe_F0henb6l7Cfq8l8M4rIRqA = $('iframe#F0henb6l7Cfq8l8M4rIRqA');

  $('.F0henb6l7Cfq8l8M4rIRqA').click(function() {
      iframe_F0henb6l7Cfq8l8M4rIRqA.attr('src', function() {
          return $(this).data('src');
      });
      $('.F0henb6l7Cfq8l8M4rIRqA').hide();
  });

  iframe_F0henb6l7Cfq8l8M4rIRqA.each(function() {
      var src = $(this).attr('src');
      $(this).data('src', src).attr('src', '');
  });

  var hash = Drupal.settings.kued_data.key;
  var iframe = 'iframe#'+hash;
  var classContainer = '.'+hash;

    $(classContainer).click(function() {
        $(iframe).attr('src', function() {
            return $(this).data('src');
        });
        
        $(classContainer).hide();
    });

    $(iframe).each(function() {
        var src = $(this).attr('src');
        $(this).data('src', src).attr('src', '');
    });
*/

    }
  };
})(jQuery);