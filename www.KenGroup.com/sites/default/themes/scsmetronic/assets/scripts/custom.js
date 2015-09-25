/**
 Custom module for you to write your own javascript functions
 **/
var Custom = function() {

  // private functions & variables

  var myFunc = function(text) {
    
  }

  // public functions
  return {
    //main function
    init: function() {
      jQuery(document).ready(function() {
        App.init();
      });
    },
    //some helper function
    doSomeStuff: function() {
      myFunc();
    }

  };

}();


Custom.init();
//Custom.doSomeStuff();