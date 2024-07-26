const PieceTypes = ['K' , 'Q' , 'R' , 'B' , 'N' , 'P' , 'k' , 'q' , 'r' , 'b' , 'n' , 'p'] as const;
const Sides = ['w', 'b'] as const;
type PieceType = typeof PieceTypes[number];
type Side = typeof Sides[number];

function isPiece(c: string){
    return PieceTypes.indexOf(c as PieceType) != -1;
}



class Piece {
    type: PieceType;
    side: Side;
    has_moved: boolean;
    constructor(type: PieceType, has_moved: boolean) {
	this.type = type;
	this.side = this.getPieceColor(type); 
	this.has_moved = has_moved;
    }

    public toString() {
	return `${this.type}`;
    }

    getPieceColor(piece: PieceType): Side{
	if (piece.toLowerCase() == piece){
	    return 'b';
	}
	return 'w';
    }

    getImgPath(): string {
	var piece_type: string = this.type.toLowerCase();
	var color: string;

	if (this.getPieceColor(this.type) == 'w') {
	    color = "l";
	} else {
	    color = "d";
	}

	return `res/${piece_type}${color}t.png`
    }
}


type BoardArray = (Piece | ' ')[];
class Board {
    board: BoardArray;
    turn: Side;
    valid_castles: Boolean[];
    en_passent: number;
    half_move: number;
    full_move: number;

    constructor(fen: string) {
	this.board = new Array(64);
	this.turn = 'w';
	this.valid_castles = [true, true, true, true]
	this.en_passent = -1;
	this.half_move = 0;
	this.full_move = 0;
	this.initializeFromFen(fen);
    }

    initializeFromFen(fen: string){
	this.board.fill(' ');

	const fen_components: string[] = fen.split(" ");
	const fen_board: string = fen_components[0];
	const fen_turn: string = fen_components[1];
	const fen_castling: string = fen_components[2];
	const fen_halfmove: string = fen_components[3];
	const fen_fullmove: string = fen_components[4];
	var i: number = 0;
	for (const c of fen_board){
	    if (isPiece(c)) {
		const current_piece = new Piece(c as PieceType, false);
		this.board[i] = current_piece;
		i++;
	    } else if (Number.isInteger(Number(c))) {
		i += parseInt(c);
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


    }

    static squareToInt(square: string){
	
    }

    fen(): string {
	var board_fen: string = "";
	var space_counter: number = 0;
	for(var i: number = 0; i < 64; ++i){
	    if (i % 8 == 0 && i != 0){
		if (space_counter > 0) {
		    board_fen += space_counter;
		    space_counter = 0;
		}
		board_fen += "/"
	    }
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
	}
	return board_fen;
    }

    public toString() {
	
	var str: String = ""
	for (var i: number = 0; i < 8; ++i){
	    // feast your eyes on this beautiful one liner
	    str += this.board.slice(i*8, (i+1) * 8).map(String).join(' ');
	    str += "\n"
	}
	return `${str}`;
    }

    getPieceAtSquare(square: number):Piece | ' '{
	return this.board[square];
    }

}



function drawBoard(board: Board) {

    const board_div = document.getElementById("board");

    if (board_div == null) {
	return;
    }

    for (let i=0; i < 64; ++i){
	const square = document.createElement("div");
	square.id = "square";

	var square_class_list = ["square"]

	if (Math.floor(i / 8) % 2 == 0) {
	    if (i % 2 == 0) {
		square_class_list.push("light");
	    } else {
		square_class_list.push("dark");
	    }
	} else {
	    if (i % 2 == 1) {
		square_class_list.push("light");
	    } else {
		square_class_list.push("dark");
	    }
	}


	square.classList.add(...square_class_list);
	if (i == 0) {
	    square.style.borderRadius = "10px 0px 0px 0px";    
	} else if (i == 7) {
	    square.style.borderRadius = "0px 10px 0px 0px";    
	} else if (i == 56) {
	    square.style.borderRadius = "0px 0px 0px 10px";    
	} else if (i == 63) {
	    square.style.borderRadius = "0px 0px 10px 0px";    
	}

	const piece_at_square: Piece | ' ' = board.getPieceAtSquare(i);
	if (piece_at_square != ' '){
	    const type: string = piece_at_square.getImgPath();
	    const piece_div = document.createElement("img");
	    piece_div.src = type;
	    piece_div.setAttribute('draggable', 'false');
	    square.appendChild(piece_div);
	}

	board_div.append(square);

	if ((i + 1) % 8 == 0) {
	    const break_div = document.createElement("div");
	    break_div.id = "break";
	    board_div.append(break_div);
	}


    }

}

const starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
const board = new Board(starting_fen);
console.log('' + board);
console.log(board.fen())
console.assert(board.fen() === starting_fen);

drawBoard(board);
