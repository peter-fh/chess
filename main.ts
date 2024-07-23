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
}


type BoardArray = (Piece | ' ')[];
class Board {
    board: BoardArray;

    constructor(fen: string) {
	this.board = new Array(64);
	this.initializeFromFen(fen);
    }

    initializeFromFen(fen: string){
	this.board.fill(' ');
	var i: number = 0;
	for (const c of fen){
	    if (isPiece(c)) {
		const current_piece = new Piece(c as PieceType, false);
		this.board[i] = current_piece;
		i++;
	    } else if (Number.isInteger(Number(c))) {
		i += parseInt(c);
	    } else if (c === ' ') {
		break;
	    }
	}
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
}




const starting_fen_full = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
const starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
const board = new Board(starting_fen);
console.log('' + board);
console.log(board.fen())
console.assert(board.fen() === starting_fen);
