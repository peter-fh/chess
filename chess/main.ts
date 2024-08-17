import {Board, Piece, Side, PieceType} from './board.js'


class State {
    board: Board;
    board_element: HTMLElement;
    clicked_piece: HTMLElement | null;
    previous_square: HTMLElement | null;
    flipped: boolean;
    constructor(){

	this.board = new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	//this.board = new Board("r3k2r/pbppqppp/1pnbpn2/8/8/1PNBPN2/PBPPQPPP/R3K2R w KQkq - 0 1");
	const board_element = document.getElementById("board");
	if (board_element == null || board_element == undefined){
	    throw new Error("Didn't find board div");
	}
	this.board_element = board_element;
	this.clicked_piece = null;
	this.previous_square = null;

	this.flipped = Math.random() < 0.5;
    }

    init(){
	drawBoard();
	validateBoard();
    }

}

function pickupPiece(e: MouseEvent) {

    if (state.clicked_piece === null) {
	return;
    }


    const piece_square = state.clicked_piece.parentNode;
    if (piece_square == null) {
	return;
    }


    piece_square.removeChild(state.clicked_piece);
    document.body.appendChild(state.clicked_piece);
    state.clicked_piece.style.position = 'absolute'
    state.clicked_piece.style.width = "75px";
    state.clicked_piece.style.height = "75px";
    var x = '' + (e.pageX - state.clicked_piece.offsetWidth / 2) + 'px';
    var y = '' + (e.pageY - state.clicked_piece.offsetHeight / 2) + 'px';
    state.clicked_piece.style.left = x;
    state.clicked_piece.style.top = y;
}

function placePiece(e: MouseEvent){
    if (state.clicked_piece == null){
	throw new Error("placing piece while state.clicked_piece is null");
    }
    if (state.previous_square == null){
	throw new Error("placing piece while previous square is null");
    }

    document.body.removeChild(state.clicked_piece);
    var cursor_element = document.elementFromPoint(e.clientX, e.clientY);
    if (cursor_element === null) {
	drawBoard();
	return;
    }

    if (cursor_element.classList.contains("piece")){
	const parent_element = cursor_element.parentElement;
	if (parent_element == null){
	    throw new Error("parent element of image is null");
	}
	cursor_element = parent_element;
    }

    if (cursor_element.id != 'square'){
	drawBoard();
	return;
    }

    const from = Number.parseInt(state.previous_square.classList[2]);
    const to = Number.parseInt(cursor_element.classList[2]);
    const moved_piece = state.board.board[from];
    if (moved_piece == ' '){
	throw new Error("Attempting to move piece that is null in board representation");
    }

    state.board.attemptMove(moved_piece, from, to);
    console.log(state.board.fen());
    drawBoard();
}


function getBoardIndex(i: number): number {
    if (state.flipped){
	return 63 - i;
    }
    return i;
}

function drawBoard() {

    if (state.board_element == null) {
	throw new Error("Attempting to find board but board is null");
    }

    state.board_element.innerHTML = "";
    state.clicked_piece = null;
    state.previous_square = null;

    for (let i = 63; i >= 0; --i) {
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

	square_class_list.push("" + getBoardIndex(i));


	square.classList.add(...square_class_list);
	if (i == 63) {
	    square.style.borderRadius = "10px 0px 0px 0px";
	} else if (i == 56) {
	    square.style.borderRadius = "0px 10px 0px 0px";
	} else if (i == 7) {
	    square.style.borderRadius = "0px 0px 0px 10px";
	} else if (i == 0) {
	    square.style.borderRadius = "0px 0px 10px 0px";
	}

	const piece_at_square: Piece | ' ' = state.board.board[getBoardIndex(i)]
	if (piece_at_square != ' ') {
	    const piece_div = document.createElement("div");
	    piece_div.onclick = function(e) {
		const piece_img = this as HTMLElement;
		if (state.clicked_piece === null) {
		    if (Piece.pieceColor(piece_img.classList[1] as PieceType) == state.board.turn){
			state.clicked_piece = piece_img;
			state.previous_square = piece_img.parentElement;
			pickupPiece(e);
		    } 
		} else {
		    placePiece(e);
		}
	    }
	    const type: string = piece_at_square.getImgPath();
	    piece_div.id = "piece";
	    piece_div.className = "piece";
	    piece_div.classList.add("piece");
	    piece_div.classList.add(piece_at_square.toString());
	    piece_div.style.backgroundImage = "url(" + type + ")"
	    square.appendChild(piece_div);
	}

	state.board_element.append(square);

	if ((i) % 8 == 0) {
	    const break_div = document.createElement("div");
	    break_div.id = "break";
	    state.board_element.append(break_div);
	}


    }

    // Board currently tests that the fen created is the same output on init
    // Creating a new board allows it to get a free test case every move
    const _ = new Board(state.board.fen());

}


function validateBoard(){
    for (var i=63; i >= 0; --i){
	const square = document.getElementsByClassName(getBoardIndex(i).toString())[0] as HTMLElement;
	const piece = square.firstChild as HTMLElement;
	if (piece == null && state.board.board[getBoardIndex(i)] != ' '){
	    throw new Error(`Board div at ${Board.intToSquare(i)} is empty but not in board class`);
	} else if (piece != null){
	    const piece_type = piece.classList[1];
	    if (piece_type != state.board.board[getBoardIndex(i)]){
		throw new Error(`Piece type at ${Board.intToSquare(i)} does not match (html: ${piece_type}, board: ${state.board.board[i]}`);
	    };
	}
    }
}

document.addEventListener("mousemove", (event) => {
    if (state.clicked_piece != null) {
	var x = '' + (event.pageX - state.clicked_piece.offsetWidth / 2) + 'px';
	var y = '' + (event.pageY - state.clicked_piece.offsetHeight / 2) + 'px';
	state.clicked_piece.style.left = x;
	state.clicked_piece.style.top = y;
    }
})


const state = new State();
state.init();
