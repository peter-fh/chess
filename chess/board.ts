// TODO castling
// TODO en passant
// TODO pawn promotion

export const PieceTypes = ['K', 'Q', 'R', 'B', 'N', 'P', 'k', 'q', 'r', 'b', 'n', 'p'] as const;
export const Sides = ['w', 'b'] as const;
export type PieceType = typeof PieceTypes[number];
export type Side = typeof Sides[number];

export function isPiece(c: string) {
    return PieceTypes.indexOf(c as PieceType) != -1;
}




export class Piece {
    type: PieceType;
    side: Side;
    has_moved: boolean;
    constructor(type: PieceType, has_moved: boolean) {
	this.type = type;
	this.side = Piece.pieceColor(type);
	this.has_moved = has_moved;
    }

    public toString() {
	return `${this.type}`;
    }

    static pieceColor(piece: PieceType){
	if (piece.toLowerCase() == piece) {
	    return 'b';
	}
	return 'w';
    }
    getPieceColor(): Side {
	if (this.type.toLowerCase() == this.type) {
	    return 'b';
	}
	return 'w';
    }

    getImgPath(): string {
	var piece_type: string = this.type.toLowerCase();
	var color: string;

	if (this.getPieceColor() == 'w') {
	    color = "l";
	} else {
	    color = "d";
	}

	return `res/${piece_type}${color}t.png`
    }
}


class Move {
    piece: Piece;
    to: number;
    from: number;
    x_from: number;
    y_from: number;
    x_to: number;
    y_to: number;
    dx: number;
    dy: number;
    is_legal: boolean;
    is_castle: boolean;
    is_en_passent: boolean;
    constructor(piece: Piece, from: number, to: number){
	this.piece = piece;
	this.from = from;
	this.to = to;
	this.x_from = from % 8;
	this.y_from = Math.floor(from / 8);
	this.x_to = to % 8;
	this.y_to = Math.floor(to / 8);
	this.dx = this.x_to - this.x_from;
	this.dy = this.y_to - this.y_from;
	this.is_legal = false;
	this.is_castle = false;
	this.is_en_passent = false;
    }
}


export type BoardArray = (Piece | ' ')[];
export class Board {
    board: BoardArray;
    turn: Side;
    valid_castles: boolean[];
    en_passent: number;
    half_move: number;
    full_move: number;

    constructor(fen: string) {
	this.board = new Array(64);
	this.turn = 'w';
	this.valid_castles = [false, false, false, false]
	this.en_passent = -1;
	this.half_move = 0;
	this.full_move = 0;
	this.initializeFromFen(fen);
    }

    initializeFromFen(fen: string) {
	this.board.fill(' ');

	const fen_components: string[] = fen.split(" ");
	const fen_board: string = fen_components[0];
	const fen_turn: string = fen_components[1];
	const fen_castling: string = fen_components[2];
	const fen_en_passent: string = fen_components[3];
	const fen_halfmove: string = fen_components[4];
	const fen_fullmove: string = fen_components[5];
	var i: number = 63;
	for (const c of fen_board) {
	    if (isPiece(c)) {
		const current_piece = new Piece(c as PieceType, false);
		this.board[i] = current_piece;
		i--;
	    } else if (Number.isInteger(Number(c))) {
		i -= parseInt(c);
	    }
	}

	if (fen_turn == 'w' || fen_turn == 'b') {
	    this.turn = fen_turn;
	} else {
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
	} else {
	    this.en_passent = Board.squareToInt(fen_en_passent);
	}

	this.half_move = +fen_halfmove;
	this.full_move = +fen_fullmove;
	if (this.fen() != fen) {
	    console.log("In fen:", fen);
	    console.log("Out fen:", this.fen());
	    throw new Error("input fen does not equal initialized board");
	} 


    }

    static squareToInt(square: string): number {
	const row_number: number = 7 - (square.charCodeAt(0) - 'a'.charCodeAt(0));
	const column_number: number = (square.charCodeAt(1) - 1) - '0'.charCodeAt(0);
	return column_number * 8 + row_number;
    }

    static intToSquare(square: number): string {
	const row_letter: string = String.fromCharCode('a'.charCodeAt(0) + 7 - (square % 8))
	const column_number: number = Math.floor(square / 8) + 1;
	return row_letter + column_number;
    }


    fen(): string {
	var board_fen: string = "";
	var space_counter: number = 0;
	for (var i: number = 63; i >= 0; --i) {
	    var c: (Piece | ' ') = this.board[i];
	    if (c instanceof Piece) {
		if (space_counter > 0) {
		    board_fen += space_counter;
		    space_counter = 0;
		}
		board_fen += c.toString();
	} else if (c == ' ') {
		space_counter++
	    } else {
		throw new Error("board has non-piece non-space element");
	    }
	    if ((i) % 8 == 0 && i != 0) {
		if (space_counter > 0) {
		    board_fen += space_counter;
		    space_counter = 0;
		}
		if (i != 63) {
		    board_fen += "/"
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
	    board_fen += " -"
	} else {
	    board_fen += " " + Board.intToSquare(this.en_passent);
	}
	board_fen += " " + this.half_move;
	board_fen += " " + this.full_move;

	return board_fen;
    }


    makeMove(move: Move){

	const from = move.x_from + move.y_from * 8;
	const to = move.x_to + move.y_to * 8;

	if (this.board[from] == ' '){
	    throw new Error("Making move when 'from' square has no piece");
	}

	if (move.is_castle){
	    var king_from: number;
	    var king_to: number;
	    var rook_from: number;
	    var rook_to: number;
	    if (move.piece.type == 'K'){
		king_from = 3;
		if (to < from) { // Kingside
		    king_to = 1;
		    rook_from = 0;
		    rook_to = 2;
		} else { // Queenside
		    king_to = 5;
		    rook_from = 7;
		    rook_to = 4;
		}
	    } else if (move.piece.type == 'k'){
		king_from = 59;
		if (to < from) { // Kingside
		    king_to = 57;
		    rook_from = 56;
		    rook_to = 58;
		} else { // Queenside
		    king_to = 61;
		    rook_from = 63;
		    rook_to = 60;
		}
	    } else {
		throw new Error("trying to castle in makeMove but moved piece is not a king");
	    }
	    const king = this.board[king_from];
	    const rook = this.board[rook_from];
	    if (king == ' ' || rook == ' '){
		throw new Error("Trying to castle but king or rook is not at its starting square");
	    }
	    king.has_moved = true;
	    rook.has_moved = true;
	    this.board[king_to] = this.board[king_from];
	    this.board[king_from] = ' ';
	    this.board[rook_to] = this.board[rook_from];
	    this.board[rook_from] = ' ';
	    const test_king = this.board[king_to];
	    if (test_king == ' '){
		throw new Error("Just placed king is somehow null");
	    } else {
		if (test_king.has_moved == false){
		    throw new Error("King.has_moved is false but castle was just completed");
		} else {
		    console.log("all good from the castle!!!");
		}
	    }
	} else {
	    this.board[to] = this.board[from];
	    this.board[from] = ' ';
	}

	if (this.turn == 'b'){
	    this.turn = 'w';
	} else {
	    this.turn = 'b';
	}
    }

    public getPieceAtSquare(x: number, y: number): Piece | ' ' {
	return this.board[x+y*8];
    }

    isDiagonalMove(move: Move): boolean{
	if (!(Math.abs(move.dx) == Math.abs(move.dy))){
	    return false;
	}


	const x_iter = Math.floor(move.dx / Math.abs(move.dx));
	const y_iter = Math.floor(move.dy / Math.abs(move.dy));
	var x = move.x_from + x_iter;
	var y = move.y_from + y_iter;
	while (x != move.x_to){
	    if (this.getPieceAtSquare(x, y) != ' '){
		return false;
	    }
	    x += x_iter;
	    y += y_iter;
	}

	if (y != move.y_to){
	    throw new Error("Diagonal move check reached final row without reaching final column");
	}
	return true;
    }

    isSlidingMove(move: Move): boolean {
	if (!(move.dx == 0 || move.dy == 0)){
	    return false;
	}

	var x_iter = Math.floor(move.dx / Math.abs(move.dx));
	var y_iter = Math.floor(move.dy / Math.abs(move.dy));
	if (move.dx == 0){
	    x_iter = 0;
	}
	if (move.dy == 0){
	    y_iter = 0;
	}
	var x = move.x_from + x_iter;
	var y = move.y_from + y_iter;
	while (x != move.x_to || y != move.y_to){
	    if (this.getPieceAtSquare(x, y) != ' '){
		return false;
	    }
	    x += x_iter;
	    y += y_iter;
	}

	return true;
    }

    isKnightMove(move: Move): boolean{

	if (Math.abs(move.dx) == 2 && Math.abs(move.dy) == 1){
	    return true;
	}

	if (Math.abs(move.dx) == 1 && Math.abs(move.dy) == 2){
	    return true;
	}

	return false;
	
    }

    isPawnMove(move: Move, side: Side): boolean {
	if (side == 'w'){
	    if (move.dy == 1 && move.dx == 0){
		if (this.getPieceAtSquare(move.x_to, move.y_to) == ' '){
		    return true;
		}
	    }

	    if (move.dy == 2 && move.dx == 0){
		if (move.y_from == 1 && this.getPieceAtSquare(move.x_from, move.y_from+1) == ' '){
		    if (this.getPieceAtSquare(move.x_to, move.y_to) == ' '){
			return true;
		    }
		}
	    }

	    if (move.dy == 1 && Math.abs(move.dx) == 1 && this.getPieceAtSquare(move.x_to, move.y_to) != ' '){
		return true;
	    }
	}

	if (side == 'b'){
	    if (move.dy == -1 && move.dx == 0){
		if (this.getPieceAtSquare(move.x_to, move.y_to) == ' '){
		    return true;
		}
	    }

	    if (move.dy == -2 && move.dx == 0){
		if (move.y_from == 6 && this.getPieceAtSquare(move.x_from, move.y_from-1) == ' '){
		    if (this.getPieceAtSquare(move.x_to, move.y_to) == ' '){
			return true;
		    }
		}
	    }

	    if (move.dy == -1 && Math.abs(move.dx) == 1 && this.getPieceAtSquare(move.x_to, move.y_to) != ' '){
		return true;
	    }
	}
	return false;
    }

    isKingMove(move: Move): boolean{
	if (!this.isSlidingMove(move) && !this.isDiagonalMove(move)){
	    return false;
	}

	if (Math.abs(move.dx) > 1 || Math.abs(move.dy) > 1){
	    return false;
	}

	return true;
    }

    isCastle(move: Move): boolean{
	if (move.piece.has_moved) {
	    return false;
	}
	var rook: Piece | ' ';
	if (move.piece.type === 'K'){
	    if (move.to === 1 || move.to === 0){
		if (this.board[1] != ' ' || this.board[2] != ' '){
		    return false;
		}
		rook = this.board[0];
	    } else if (move.to === 5 || move.to === 7) {
		rook = this.board[7];
		if (this.board[4] != ' ' || this.board[5] != ' ' || this.board[6] != ' '){
		    return false;
		}
	    } else {
		return false;
	    }
	} else if (move.piece.type === 'k') {
	    if (move.to === 57 || move.to === 56){
		if (this.board[58] != ' ' || this.board[57] != ' '){
		    return false;
		}
		rook = this.board[56];
	    } else if (move.to === 61 || move.to === 63) {
		if (this.board[61] != ' ' || this.board[60] != ' '|| this.board[62] != ' '){
		    return false;
		}
		rook = this.board[63];
	    } else {
		return false;
	    }
	} else {
	    return false;
	}

	if (rook === ' '){
	    return false;
	}

	if (rook.has_moved){
	    return false;
	}

	return true;
    }

    isLegal(piece: Piece, from: number, to: number): Move {
	const move = new Move(piece, from, to);
	const type = piece.type;
	const side = piece.side;
	if (to === from) {
	    return move;
	}
	const to_piece = this.board[to];

	if (to_piece != ' ' && piece.type.toLowerCase() != 'k'){
	    if (to_piece.getPieceColor() == piece.getPieceColor()){
		return move;
	    }
	}

	if (type.toLowerCase() == 'k'){
	    if (this.isKingMove(move)){
		if (to_piece == ' '){
		    move.is_legal = true;
		    return move;
		} else if (to_piece.getPieceColor() != piece.getPieceColor()){
		    move.is_legal = true;
		    return move;
		}
	    } else if (this.isCastle(move)){
		move.is_legal = true;
		move.is_castle = true;
		return move;
	    }
	}
	if (type.toLowerCase() == 'q'){
	    if (this.isSlidingMove(move)){
		move.is_legal = true;
		return move;
	    }
	    if (this.isDiagonalMove(move)){
		move.is_legal = true;
		return move;
	    }
	}
	if (type.toLowerCase() == 'r'){
	    if (this.isSlidingMove(move)){
		move.is_legal = true;
		return move;
	    }
	}
	if (type.toLowerCase() == 'b'){
	    if (this.isDiagonalMove(move)){
		move.is_legal = true;
		return move;
	    }
	}
	if (type.toLowerCase() == 'n'){
	    if (this.isKnightMove(move)){
		move.is_legal = true;
		return move;
	    }
	}
	if (type.toLowerCase() == 'p'){
	    if (this.isPawnMove(move, side)){
		move.is_legal = true;
		return move;
	    }
	}


	return move;
    }


    attemptMove(piece: Piece, from: number, to: number) {
	const move = this.isLegal(piece, from, to);
	if (move.is_legal){
	    this.makeMove(move);
	}
    }
    public toString() {

	var str: String = ""
	for (var i: number = 0; i < 8; ++i) {
	    str += this.board.slice(i * 8, (i + 1) * 8).map(String).join(' ');
	    str += "\n"
	}
	return `${str}`;
    }



}
