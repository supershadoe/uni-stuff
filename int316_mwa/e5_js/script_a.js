const val = parseInt(prompt("Enter a number."));
if (val <= 0) {
    alert("Invalid input, provide a val > 0");
    document.write("No O/P")
} else {
    let num = val;
    let digits = 0;
    while (num !== 0) {
        num = Math.floor(num / 10);
        digits++;
    }
    document.write(`Number of digits in ${val} is ${digits}`);
}