(function() {
'use-strict';
angular.module('firebaseService',[])
.factory('firebaseService', firebaseService);

firebaseService.$inject = ['$firebaseArray'];
function firebaseService($firebaseArray) {
    var database = firebase.database().ref().child('input');

    var functions = {
      getAll: getAll
    };

    function getAll() {
      return $firebaseArray(database);
    };

    return functions;
}
})();
