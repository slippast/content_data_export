(function ($) {
    Drupal.ajax.prototype.commands.customViewsScrollTop = function (ajax, response, status) {
      // Scroll to the top of the view. This will allow users
      // to browse newly loaded content after e.g. clicking a pager
      // link.
      var offset = $(response.selector).offset();
      // We can't guarantee that the scrollable object should be
      // the body, as the view could be embedded in something
      // more complex such as a modal popup. Recurse up the DOM
      // and scroll the first element that has a non-zero top.
      var scrollTarget = response.selector;
      while ($(scrollTarget).scrollTop() == 0 && $(scrollTarget).parent()) {
        scrollTarget = $(scrollTarget).parent();
        }
        var header_height = 107;
        // Only scroll upward
        if (offset.top - header_height < $(scrollTarget).scrollTop()) {
        $(scrollTarget).animate({scrollTop: (offset.top - header_height)}, 500);
      }
    };
})(jQuery); 