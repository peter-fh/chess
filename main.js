"use strict";
var Piece = /** @class */ (function () {
    function Piece(type, side, has_moved) {
        this.type = type;
        this.side = side;
        this.has_moved = has_moved;
    }
    Piece.prototype.toString = function () {
        return "".concat(this.type);
    };
    return Piece;
}());
var Board = /** @class */ (function () {
    function Board(fen) {
        this.board = new Array(64);
        this.initializeFromFen(fen);
    }
    Board.prototype.initializeFromFen = function (fen) {
        this.board.fill(null);
        var i = 0;
        for (var _i = 0, fen_1 = fen; _i < fen_1.length; _i++) {
            var c = fen_1[_i];
            try {
                console.log(c);
                console.log("yes");
            }
            catch (_a) {
                console.log("no");
            }
        }
    };
    Board.prototype.fen = function () {
        return "";
    };
    return Board;
}());
var starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
var board = new Board(starting_fen);
console.assert(board.fen() === starting_fen);
