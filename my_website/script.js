var heading = 'TK Fun Story';
let i = 0;

function typing (){
//var typing = () => {
    if(i < heading.length) {
        document.querySelector('.heading').innerHTML += heading.charAt(i);
        i++;
        setTimeout(typing, 200);
    }
}

typing();
