	//setTimeout(function() { openCards[0].className = "blur";openCards[1].className = "blur"; } , 1000);

        var lives = 4; //lives is lives you get before you lose
        var match = 0; //match is if it is a match or not
        var reset = false; //reset is a boolean that resets the game
        var openedCards;

        function showAns(e) {

        	var target = e.target;

        	//if there are any lives left
        	if (lives > 0) {
        		if (match !== 2) {
        			if (target.querySelectorAll("img")[0].className == "blur") {
        				target.querySelectorAll("img")[0].className = "showAns";
        				match++;
        			}
        		}
        	};
        	//if there is no match (match == 2 indicates a match) and if the className is "blur", refer to this class, set the class to showAns in the css file. Then, Increment match.

        	if (match == 2 && !reset) {
        		reset = true;
				openedCards = document.querySelectorAll(".showAns");
        		//blur, revealed, & showAns
        	};
        	//if there is a match and the game isn't reset, set the reset to true. Set a variable to the document.querySelectorAll() method. Use the appropriate class from the css file. Hint: you are revealing the answer. See the above note.
        	if (reset&&typeof openedCards !== 'undefined' && openedCards[0].src !== openedCards[1].src) {
				lives--;
        		setTimeout(function(){
					openedCards = document.querySelectorAll(".showAns");
					for (var i = 0; i < openedCards.length; i++) {
						openedCards[i].className = "blur";
					}
				}, 3000);
        		match = 0;
        		reset = false;
        		openedCards = [];
        	}


        			//if the revealed variable source's (src) current position (0th position) is not the one that is guessed next to it, then the guess is wrong. Lose a life. (***HINT::: the variable must be an array.) Set the timeout to an anonymous function that is a for loop. The for loop cycles over the revealed array, setting the ith position of the array to the className method to the "blur" css setting. Set match to 0. Set reset to false.


        			if (lives == 0) {

        				var end = document.getElementById("endgame");
        				end.innerHTML = "You lose";
        				end.style.color = "red";
        				end.style.left = "";
        				end.style.top = "";

        				//if there are no lives left, get the "endgame" id from the css file via the document window. (document.getElementById()). Display "You lose" either to the document window using innerHTML in big red letters and centered on the screen. (You will have to center the text to the left and top of the screen by using end.style.left and end.style.top, respectively. The end.style.color element should be "red". The screen width and height are always measured in pixels. **If you wish, you can also use another method to display "you lose" if this doesn't work for you.**

        				/******the middle of the screen is the center-point of the left and the top of the screen
        				Therefore the left is the total number of pixels - end.clientWidth/2 Ex. 900 - end.clientWidth/2. Rinse and repeat for the clientHeight*****/

        			} else {

						
						//match = 0;
						//reset = false;
        			}; //else it is a correct guess. Both revealed pictures match. So set the same timeOut anonymous function and cycle through the ith position of the revealed array, as above, but this time set the className to "blur" and the parentNode of the className to "revealed". Reset the match to 0 and the reset to false.

        			//next check for a win.

        			if (document.querySelectorAll(".revealed").length == 12) {

        				var end = document.getElementById("endgame");
        				end.innerHTML = "You win";
        				end.style.color = "blue";
        				end.style.left = "";
        				end.style.top = "";

        			};
        			// A win is when all the tiles of the 3x4 grid has been matched. So 3x4 = 12 Thus, if the (document.querySelectorAll(".revealed").length is the same as 12, then show "You win" in the same way that you did that with the innerHTML code for "You lose." Same code. Except make the text color blue.

        		}; //end function ShowAns()

        		function init() {



        			//var seq is sequence of matches in array form. Initialize in pairs as "001122334455"
        			var seq = "001122334455";
        			var scramble = ""; //var scramble is empty string

        			var filenames = ["zero", "one", "two", "three", "four", "five"]; //var filenames is the array of files: zero, one, two, three, four, five.

        			while (seq.length) {
        				var index = Math.floor(Math.random() * seq.length);
        				scramble += seq.charAt(index);
        				seq = seq.replace(seq.charAt(index), '');
        			}; //while seq.length, set Math.floor(Math.random times the seq length). increment scramble += seq.charAt the random varlocation above. set seq to replace the character at the random var location with a space ' ')


        			for (var i = 0; i < scramble.length; i++) { //for the length of the scramble array, from 0 to length


        				var img = document.createElement("img");
        				var div = document.createElement("div"); //set a var wrapper to the "div" tag and the "img" tag


        				img.className = "blur";
        				//use the className and set the variable holding the img tag to the class "blur"


        				//next we have to replace the image as hidden. In this game, blur is hidden.

        				img.src = filenames[parseInt(scramble.charAt(i))] + ".jpg";

        				div.addEventListener('click', showAns);
        				div.appendChild(img);
        				document.getElementById("game").appendChild(div);

        				//img.style.opacity = 1;
        				//then set the src tag to the charAt of the scramble of the filenames array. Parse the scramble as an int using parseInt. Append ".jpg" to the end the filename. Append the child (appendChild) to the wrapper using the listener, e, as an argument. Get the id element, "game" from the css file and append the child (appendChild) to the "game" id element of the document.

        				document.querySelectorAll("game");

        				//set a new variable image to the game div tag using document.querySelectorAll() function. the game div tag goes inside.
        			};
        			for (var i = 0; i > img.length; i++) {
        				window.onclick = showAns;
        			};
        			//for the entire image.length from 0 to the length of image, cycle over the array using the onclick method and set that to showAns. Then call reposition () function.
        			reposition();
        		}; //end init () function

        		function reposition() { //start reposition() function

        			var board = document.getElementById("game");
        			board.style.left = (document.getElementsByTagName("body")[0].clientWidth - 896) / 2 + "px";
        			board.style.top = (document.getElementsByTagName("body")[0].clientHeight + 170) / 2 + "px";

        			//set the width (left) and the height (top) of the screen to the center as described above.
        			//Size of screen or size of value. When getting it diving by 2, we can get it to the center.

        		}; //end reposition() function

        		window.onload = init; //call window.onload = init to start everything
