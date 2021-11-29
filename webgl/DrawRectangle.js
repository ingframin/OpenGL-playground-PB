
function main(){
    var canvas = document.getElementById("drwcanvas");
    if(!canvas){
        console.log("Error loading canvas");
        return;
    }
    var ctx = canvas.getContext("2d");
    ctx.fillStyle =  'rgba(0, 0, 255, 1.0)';
    ctx.fillRect(100,100,500,500);

}