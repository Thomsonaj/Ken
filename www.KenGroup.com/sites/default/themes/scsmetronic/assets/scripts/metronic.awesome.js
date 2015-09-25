(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.metronic_awesome = {
    attach:function (context) {
      $('.awesome').bind('click', function(){
        Drupal.settings.awesome = $(this);
        $('#awesome_fonts').show();
      });
      $('#awesome_fonts i.fa.fa-check').bind('click', function(){
        $('#awesome_fonts').hide();
        var newClass = $(this).attr('key');
        Drupal.settings.awesome.removeClass(Drupal.settings.awesome.attr('key'))
        Drupal.settings.awesome.addClass(newClass);
        Drupal.settings.awesome.attr('key', newClass);
        $('[name="' + Drupal.settings.awesome.attr('href') + '"]').val(newClass);
      });
      $('a.cancel').bind('click', function(){
        $('#awesome_fonts').hide();
      });
      $('a.trash').bind('click', function(){
        $('#awesome_fonts').hide();
        var newClass = 'fa-plus';
        Drupal.settings.awesome.removeClass(Drupal.settings.awesome.attr('key'))
        Drupal.settings.awesome.addClass(newClass);
        Drupal.settings.awesome.attr('key', newClass);
        $('[name="' + Drupal.settings.awesome.attr('href') + '"]').val('');
      });
    }
  }
})(jQuery, Drupal, this, this.document);
