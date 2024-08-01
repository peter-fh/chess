// TODO castling
// TODO en passant
// TODO pawn promotion

export const PieceTypes = ['K', 'Q', 'R', 'B', 'N', 'P', 'k', 'q', 'r', 'b', 'n', 'p'] as const;
export const Sides = ['w', 'b'] as const;
export type PieceType = typeof PieceTypes[number];
export type Side = typeof Sides[number];
export type MoveType = 'VALID_PASSIVE' | 'VALID_TAKE' | 'VALID_PROMOTION' | 'VALID_CASTLE' | 'INVALID'
type MovePattern = 'SLIDING' | 'DIAGONAL' | 'L'

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
	x_from: number;
	y_from: number;
	x_to: number;
	y_to: number;
	dx: number;
	dy: number;
    constructor(from: number, to: number){
	this.x_from = from % 8;
	this.y_from = Math.floor(from / 8);
	this.x_to = to % 8;
	this.y_to = Math.floor(to / 8);
	this.dx = this.x_to - this.x_from;
	this.dy = this.y_to - this.y_from;
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
	for (var i: number = 0; i < 64; ++i) {
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
	    if ((i + 1) % 8 == 0 && i != 0) {
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

    makeMove(from: number, to: number){

	if (this.board[from] == ' '){
	    throw new Error("Making move when from square has no piece");
	}
	this.board[to] = this.board[from];
	this.board[from] = ' ';

	if (this.turn == 'b'){
	    this.turn = 'w';
	} else {
	    this.turn = 'b';
	}
    }

    static getMovePattern(from: number, to: number): MovePattern | null {
	const x_from = from % 8;
	const y_from = Math.floor(from / 8);
	const x_to = to % 8;
	const y_to = Math.floor(to / 8);
	const dx = x_to - x_from;
	const dy = y_to - y_from;
	if (Math.abs(dx) == Math.abs(dy)){
	    return 'DIAGONAL';
	}

	if (dx == 0 || dy == 0){
	    return 'SLIDING';
	}

	if (Math.abs(dx) == 2 && Math.abs(dy) == 1){
	    return 'L';
	}

	if (Math.abs(dx) == 1 && Math.abs(dy) == 2){
	    return 'L';
	}

	return null;

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

    isSlidingMove(move: Move): boolean{
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
	    console.log("x:", x);
	    console.log("y:", y);
	    if (this.getPieceAtSquare(x, y) != ' '){
		console.log(this.getPieceAtSquare(x, y));
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

    isLegal(piece: Piece, from: number, to: number): boolean {
	const move = new Move(from, to);
	const type = piece.type;
	const side = piece.side;
	if (type.toLowerCase() == 'k'){
	    if (this.isKingMove(move)){
		return true;
	    }
	}
	if (type.toLowerCase() == 'q'){
	    if (this.isSlidingMove(move)){
		return true;
	    }
	    if (this.isDiagonalMove(move)){
		return true;
	    }
	}
	if (type.toLowerCase() == 'r'){
	    if (this.isSlidingMove(move)){
		return true;
	    }
	}
	if (type.toLowerCase() == 'b'){
	    if (this.isDiagonalMove(move)){
		return true;
	    }
	}
	if (type.toLowerCase() == 'n'){
	    if (this.isKnightMove(move)){
		return true;
	    }
	    console.log("invalid knight move");
	}
	if (type.toLowerCase() == 'p'){
	    if (this.isPawnMove(move, side)){
		return true;
	    }
	}


	return false;
    }


    moveType(piece: Piece, from: number, to: number) : MoveType {
	var take = false;
	if (to === from){
	    return "INVALID";
	} 

	const move_pattern = Board.getMovePattern(from, to);
	if (move_pattern == null){
	    return "INVALID";
	}

	if (!this.isLegal(piece, from, to)){
	    return "INVALID"
	}

	const to_piece = this.board[to];
	if (to_piece != ' '){
	    if (to_piece.getPieceColor() == piece.getPieceColor()){
		take = true;
	    }
	}

	return "VALID_PASSIVE";
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
