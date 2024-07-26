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
    Piece.prototype.getImgPath = function () {
        var piece_type = this.type.toLowerCase();
        var color;
        if (this.getPieceColor(this.type) == 'w') {
            color = "l";
        }
        else {
            color = "d";
        }
        return "res/".concat(piece_type).concat(color, "t.png");
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
    Board.prototype.getPieceAtSquare = function (square) {
        return this.board[square];
    };
    return Board;
}());
function drawBoard(board) {
    var _a;
    var board_div = document.getElementById("board");
    if (board_div == null) {
        return;
    }
    for (var i = 0; i < 64; ++i) {
        var square = document.createElement("div");
        square.id = "square";
        var square_class_list = ["square"];
        if (Math.floor(i / 8) % 2 == 0) {
            if (i % 2 == 0) {
                square_class_list.push("light");
            }
            else {
                square_class_list.push("dark");
            }
        }
        else {
            if (i % 2 == 1) {
                square_class_list.push("light");
            }
            else {
                square_class_list.push("dark");
            }
        }
        (_a = square.classList).add.apply(_a, square_class_list);
        if (i == 0) {
            square.style.borderRadius = "10px 0px 0px 0px";
        }
        else if (i == 7) {
            square.style.borderRadius = "0px 10px 0px 0px";
        }
        else if (i == 56) {
            square.style.borderRadius = "0px 0px 0px 10px";
        }
        else if (i == 63) {
            square.style.borderRadius = "0px 0px 10px 0px";
        }
        var piece_at_square = board.getPieceAtSquare(i);
        if (piece_at_square != ' ') {
            var type = piece_at_square.getImgPath();
            var piece_div = document.createElement("img");
            piece_div.src = type;
            piece_div.setAttribute('draggable', 'false');
            square.appendChild(piece_div);
        }
        board_div.append(square);
        if ((i + 1) % 8 == 0) {
            var break_div = document.createElement("div");
            break_div.id = "break";
            board_div.append(break_div);
        }
    }
}
var starting_fen_full = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
var starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
var board = new Board(starting_fen);
console.log('' + board);
console.log(board.fen());
console.assert(board.fen() === starting_fen);
drawBoard(board);
