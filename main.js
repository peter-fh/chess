"use strict";
var PieceTypes = ['K', 'Q', 'R', 'B', 'N', 'P', 'k', 'q', 'r', 'b', 'n', 'p'];
var Sides = ['w', 'b'];
function isPiece(c) {
    return PieceTypes.indexOf(c) != -1;
}
var Piece = /** @class */ (function () {
    function Piece(type, has_moved) {
        this.type = type;
        this.side = this.getPieceColor(type);
        this.has_moved = has_moved;
    }
    Piece.prototype.toString = function () {
        return "".concat(this.type);
    };
    Piece.prototype.getPieceColor = function (piece) {
        if (piece.toLowerCase() == piece) {
            return 'b';
        }
        return 'w';
    };
    return Piece;
}());
var Board = /** @class */ (function () {
    function Board(fen) {
        this.board = new Array(64);
        this.initializeFromFen(fen);
    }
    Board.prototype.initializeFromFen = function (fen) {
        this.board.fill(' ');
        var i = 0;
        for (var _i = 0, fen_1 = fen; _i < fen_1.length; _i++) {
            var c = fen_1[_i];
            if (isPiece(c)) {
                var current_piece = new Piece(c, false);
                this.board[i] = current_piece;
                i++;
            }
            else if (Number.isInteger(Number(c))) {
                i += parseInt(c);
            }
            else if (c === ' ') {
                break;
            }
        }
    };
    Board.prototype.fen = function () {
        var board_fen = "";
        var space_counter = 0;
        for (var i = 0; i < 64; ++i) {
            if (i % 8 == 0 && i != 0) {
                if (space_counter > 0) {
                    board_fen += space_counter;
                    space_counter = 0;
                }
                board_fen += "/";
            }
            var c = this.board[i];
            if (c instanceof Piece) {
                if (space_counter > 0) {
                    board_fen += space_counter;
                    space_counter = 0;
                }
                board_fen += c.toString();
            }
            else if (c == ' ') {
                space_counter++;
            }
            else {
                throw new Error("board has non-piece non-space element");
            }
        }
        return board_fen;
    };
    Board.prototype.toString = function () {
        var str = "";
        for (var i = 0; i < 8; ++i) {
            // feast your eyes on this beautiful one liner
            str += this.board.slice(i * 8, (i + 1) * 8).map(String).join(' ');
            str += "\n";
        }
        return "".concat(str);
    };
    return Board;
}());
var starting_fen_full = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
var starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
var board = new Board(starting_fen);
console.log('' + board);
console.log(board.fen());
console.assert(board.fen() === starting_fen);
