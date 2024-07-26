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
        this.turn = 'w';
        this.valid_castles = [false, false, false, false];
        this.en_passent = -1;
        this.half_move = 0;
        this.full_move = 0;
        this.initializeFromFen(fen);
    }
    Board.prototype.initializeFromFen = function (fen) {
        this.board.fill(' ');
        var fen_components = fen.split(" ");
        var fen_board = fen_components[0];
        var fen_turn = fen_components[1];
        var fen_castling = fen_components[2];
        var fen_en_passent = fen_components[3];
        var fen_halfmove = fen_components[4];
        var fen_fullmove = fen_components[5];
        var i = 0;
        for (var _i = 0, fen_board_1 = fen_board; _i < fen_board_1.length; _i++) {
            var c = fen_board_1[_i];
            if (isPiece(c)) {
                var current_piece = new Piece(c, false);
                this.board[i] = current_piece;
                i++;
            }
            else if (Number.isInteger(Number(c))) {
                i += parseInt(c);
            }
        }
        if (fen_turn == 'w' || fen_turn == 'b') {
            this.turn = fen_turn;
        }
        else {
            throw new Error("fen turn is invalid");
        }
        if (fen_castling.includes('K')) {
            this.valid_castles[0] = true;
        }
        if (fen_castling.includes('Q')) {
            this.valid_castles[1] = true;
        }
        if (fen_castling.includes('k')) {
            this.valid_castles[2] = true;
        }
        if (fen_castling.includes('q')) {
            this.valid_castles[3] = true;
        }
        if (fen_en_passent == "-") {
            this.en_passent = -1;
        }
        else {
            this.en_passent = Board.squareToInt(fen_en_passent);
        }
        this.half_move = +fen_halfmove;
        this.full_move = +fen_fullmove;
    };
    Board.squareToInt = function (square) {
        var row_number = 7 - (square.charCodeAt(0) - 'a'.charCodeAt(0));
        var column_number = (square.charCodeAt(1) - 1) - '0'.charCodeAt(0);
        console.log("row number for", square, ":", row_number);
        console.log("column number for", square, ":", column_number);
        return column_number * 8 + row_number;
    };
    Board.intToSquare = function (square) {
        var row_letter = String.fromCharCode('a'.charCodeAt(0) + 7 - (square % 8));
        var column_number = Math.floor(square / 8) + 1;
        console.log("row letter for", square, ":", row_letter);
        console.log("column number for", square, ":", column_number);
        return row_letter + column_number;
    };
    Board.prototype.fen = function () {
        var board_fen = "";
        var space_counter = 0;
        for (var i = 0; i < 64; ++i) {
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
            if ((i + 1) % 8 == 0 && i != 0) {
                if (space_counter > 0) {
                    board_fen += space_counter;
                    space_counter = 0;
                }
                if (i != 63) {
                    board_fen += "/";
                }
            }
        }
        board_fen += " " + this.turn;
        var castling_word = "";
        if (this.valid_castles[0]) {
            castling_word += "K";
        }
        if (this.valid_castles[1]) {
            castling_word += "Q";
        }
        if (this.valid_castles[2]) {
            castling_word += "k";
        }
        if (this.valid_castles[3]) {
            castling_word += "q";
        }
        if (!(this.valid_castles[0] || this.valid_castles[1] || this.valid_castles[2] || this.valid_castles[3])) {
            if (castling_word !== "") {
                throw new Error("Setting castling string to nil when it is non-empty");
            }
            castling_word = "-";
        }
        board_fen += " " + castling_word;
        if (this.en_passent === -1) {
            board_fen += " -";
        }
        else {
            board_fen += " " + Board.intToSquare(this.en_passent);
        }
        board_fen += " " + this.half_move;
        board_fen += " " + this.full_move;
        return board_fen;
    };
    Board.prototype.toString = function () {
        var str = "";
        for (var i = 0; i < 8; ++i) {
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
function assertFen(fen) {
    var test_board = new Board(fen);
    console.log("Testing fen");
    console.log(fen);
    console.log(test_board.fen());
    drawBoard(test_board);
}
var test_fen = "4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1";
var starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
//assertFen(test_fen);
assertFen(starting_fen);
//const board = new Board(test_fen);
