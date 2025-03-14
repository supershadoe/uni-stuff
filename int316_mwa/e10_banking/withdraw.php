<?php
    session_start();
    $user_details = array();
    $conn = new mysqli("localhost", "lab_user", "hello123", "banking_system");
    if (! $conn) {
        die("Failed to connect to database.");
    }
    if (! isset($_SESSION["auth"])) {
        header("Location: login.php");
    } else {
        $res = $conn->query("SELECT username, balance FROM customers WHERE customer_id = '".$_SESSION["auth"]."';");
        $user_details = $res->fetch_assoc();
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Withdraw | XYZ Bank</title>
    <link href="style.css" rel="stylesheet">
</head>
<body>
    <nav>
        <div>
            XYZ BANK
        </div>
        <div>
            <div><a href="deposit.php">Deposit</a></div>
            <div><a href="withdraw.php">Withdraw</a></div>
            <div><a href="logout.php">Sign out</a></div>
        </div>
    </nav>
    <main>
        <div class="text-2xl">
            Withdraw amount.
        </div>
        <div class="text-xl">
            Your account balance is $<span class="text-medium">
                <?php echo $user_details["balance"] ?>
            </span>
        </div>
        <form action="transact.php" method="post">
            <label for="amt">Enter amount to withdraw</label>
            <input id="amt" name="amt" type="number" required />
            <input name="t_type" type="hidden" value="DB" />
            <input type="submit" class="btn bg-blue text-white" value="Withdraw" />
        </form>
</body>
</html>
