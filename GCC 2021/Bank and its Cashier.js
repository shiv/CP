var stdin_input = "";

process.stdin.on("data", function (input) {
    stdin_input += input;
});

process.stdin.on("end", function () {
   main(stdin_input);
});

function main(input) {
    var n = parseInt(input, 10);
    var ans = Math.floor(n / 3);
    ans *= 2;
    ans += n % 3 != 0;
    console.log(ans);
}