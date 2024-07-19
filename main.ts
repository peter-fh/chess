const PieceTypes = ['K' , 'Q' , 'R' , 'B' , 'N' , 'P' , 'k' , 'q' , 'r' , 'b' , 'n' , 'p'] as const;
const Sides = ['w', 'b'] as const;
type PieceType = typeof PieceTypes[number];
type Side = typeof Sides[number];



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


type BoardArray = (Piece | null)[];
class Board {
    board: BoardArray;

    constructor(fen: string) {
	this.board = new Array(64);
	this.initializeFromFen(fen);
    }

    initializeFromFen(fen: string){
	this.board.fill(null);
	var i: number = 0;
	for (const c of fen){
	    if (c in PieceTypes) {
		const current_piece = new Piece(c as PieceType, false);
		this.board[i] = current_piece;
		i++;
	    }
	}
    }

    fen(): string {
	return "";
    }
}


const starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
const board = new Board(starting_fen);
console.assert(board.fen() === starting_fen);
