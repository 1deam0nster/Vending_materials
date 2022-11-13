
// Get the modal
var modal = document.getElementById("myModal");

// Get the button that opens the modal
// var btn = document.getElementById("myBtn");

// Get the <span> element that closes the modal
var span = document.getElementsByClassName("modal-close")[0];

// modal.style.display = "block";

// When the user clicks on the button, open the modal
// btn.onclick = function () {
//     modal.style.display = "block";
// }

// When the user clicks on <span> (x), close the modal
span.onclick = function () {
    modal.style.display = "none";
}

// When the user clicks anywhere outside of the modal, close it
window.onclick = function (event) {
    if (event.target == modal) {
        modal.style.display = "none";
    }
}

let coffe_state = 1;
let cream_state = 0;
let choco_state = 0;
let coffe_price = document.querySelector('.item_value_price').innerText.replace('₽ / 50 МЛ', '');
let cream_price = document.querySelector('.title_cream_price').innerText.replace('+', '');
let choco_price = document.querySelector('.title_choco_price').innerText.replace('+', '');
let total_price;

console.log(coffe_price);
console.log(cream_price);
console.log(choco_price);
var coffe_pr, cream_pr;

function check() {
    var getCreamValue = document.querySelector('input[name="cream"]:checked').value;
    if (getCreamValue == 0) {
        cream_state = 0;
    } else if (getCreamValue == 1) {
        cream_state = 1;
    } else if (getCreamValue == 2) {
        cream_state = 2;
    };

    var getChocoValue = document.querySelector('input[name="choco"]:checked').value;
    if (getChocoValue == 0) {
        choco_state = 0;
    } else if (getChocoValue == 1) {
        choco_state = 1;
    } else if (getChocoValue == 2) {
        choco_state = 2;
    };

    var getCoffeValue = document.querySelector('input[name="item"]:checked').value;
    if (getCoffeValue == 1) {
        coffe_state = 1;
    } else if (getCoffeValue == 2) {
        coffe_state = 2;
    };
    calc(coffe_state, coffe_price, cream_state, cream_price, choco_state, choco_price);
};

calc(coffe_state, coffe_price, cream_state, cream_price, choco_state, choco_price);

function calc(coffe_state, coffe_price, cream_state, cream_price, choco_state, choco_price) {
    if (coffe_state == 1) {
        coffe_pr = coffe_price;
    } if (coffe_state == 2) {
        coffe_pr = coffe_price * 2;
    };
    console.log(coffe_pr)

    if (cream_state == 0) {
        cream_pr = 0;
    } if (cream_state == 1) {
        cream_pr = cream_price;
    } if (cream_state == 2) {
        cream_pr = cream_price * 2;
    };
    console.log(cream_pr);

    if (choco_state == 0) {
        choco_pr = 0;
    } if (choco_state == 1) {
        choco_pr = choco_price;
    } if (choco_state == 2) {
        choco_pr = choco_price * 2;
    };
    console.log(choco_pr);

    cof = parseInt(coffe_pr, 10);
    crm = parseInt(cream_pr, 10);
    chc = parseInt(choco_pr, 10);
    total_price = cof + crm + chc
    console.log(total_price);
    document.getElementById('total_price').value = total_price;
    document.getElementById("price").innerHTML = total_price + "&#8381";
}

// Pressure.set('#price', {
// change: function(force){
//   this.innerHTML = force;
// }
// });
const link = '/coffe/' + document.getElementById("coffe_id").innerText

window.addEventListener("load", function () {
    function sendData() {
        const XHR = new XMLHttpRequest();

        // Bind the FormData object and the form element
        const FD = new FormData(form);

        // // Define what happens on successful data submission
        // XHR.addEventListener("load", function (event) {
        //   alert(event.target.responseText);
        // });

        // Define what happens in case of error
        XHR.addEventListener("error", function (event) {
            alert('Oops! Something went wrong.');
        });

        // Set up our request
        XHR.open("POST", link);

        // The data sent is what the user provided in the form
        XHR.send(FD);
    }

    // Access the form element...
    const form = document.getElementById("data");
    console.log(form)

    // ...and take over its submit event.
    form.addEventListener("submit", function (event) {
        event.preventDefault();
        // modal.style.display = "block";
        sendData();
    });
});
