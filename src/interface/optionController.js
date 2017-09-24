(function(){
    'use strict';
    angular.module('optionController', [])
    .controller('optionController', optionController);

    optionController.$inject = ['$scope', 'firebaseService']
    function optionController($scope, firebaseService) {
        var vm = this;
        vm.startText = "Let's JAM!";
        vm.showStage1 = true;
        vm.showStage2 = false;
        vm.showStage3 = false;
        vm.mainButton;

        vm.function1 = function() {
            vm.showStage1 = false;
            vm.showStage2 = true;
            vm.showStage3 = false;
        }

        vm.function2 = function() {
            vm.showStage1 = false;
            vm.showStage2 = false;
            vm.showStage3 = true;
        }

        vm.function3 = function() {
            // TODO: allow upto 3 selections
        }

        // TODO: implement backend for remaining functions
        vm.record = function() { var optionTable = firebaseService.getAll().$add({option: 1}); }
        vm.replay = function() { var optionTable = firebaseService.getAll().$add({option: 2}); }
        vm.merge = function() { var optionTable = firebaseService.getAll().$add({option: 3}); }
        vm.replayMerge = function() { var optionTable = firebaseService.getAll().$add({option: 4}); }
        vm.customize = function() { var optionTable = firebaseService.getAll().$add({option: 5}); }
        vm.closedHiHat = function() { }
        vm.kickA = function() { }
        vm.kickB = function() { }
        vm.openHiHat = function() { }
        vm.closedHiHat = function() { }
        vm.snare = function() { }
        vm.awesome = function() { }
        vm.closedHiHat = function() { }
        vm.boing = function(){ }
        vm.calc = function() { }
        vm.calc2 = function() { }
        vm.cashReg = function() { }
        vm.conical = function() { }
        vm.springB = function() { }
        vm.tink = function() { }
        vm.upper = function() { }
        vm.victory = function() { }
        vm.waterGL = function() { }
    }
})();
