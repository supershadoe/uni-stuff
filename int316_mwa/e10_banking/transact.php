<?php
    session_start();
    $conn = NULL;
    $error_msg = "";
    if ($_SERVER["REQUEST_METHOD"] != "POST") {
        $error_msg = "Invalid request";
    } else if (! isset($_SESSION["auth"])) {
        $error_msg = "Not authenticated";
    } else {
        $amt = $_POST["amt"];
        $txn_type = $_POST["t_type"];
        $customer_id = $_SESSION["auth"];
        $conn = new mysqli("localhost", "lab_user", "hello123", "banking_system");
        if (! $conn) {
            die("Failed to connect to database.");
        }
        $res = $conn->query("SELECT username, balance FROM customers WHERE customer_id = '$customer_id'");
        if ($res->num_rows > 0) {
            $bal = $res->fetch_assoc()['balance'];
            $new_bal = $bal;
            if ($txn_type == "CR") {
                $new_bal += $amt;
            } elseif ($txn_type == "DB") {
                if ($amt > $bal) {
                    $error_msg = "Account balance too low.";
                } else {
                    $new_bal -= $amt;
                }
            }
            $res->close();
            $r1 = $conn->query("UPDATE customers SET balance = $new_bal WHERE customer_id = '$customer_id';");
            $txn_id = time();
            $txn_date = '2024-10-18';
            $r2 = $conn->query("INSERT INTO transactions (transaction_id, customer_id, amount, transaction_type, transaction_date) VALUES ($txn_id, '$customer_id', $amt, '$txn_type', '$txn_date');");
            if ($r1 && $r2) {
                header("Location: dashboard.php");
            } else {
                $error_msg = "Failed to perform transaction.";
            }
        } else {
            $error_msg = "User not found";
        }
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Transaction error | XYZ Bank</title>
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
            Transaction failed.
        </div>
        <div>Your transaction failed with the error message: <?php echo $error_msg ?></div>
        <a href="dashboard.php" class="btn bg-blue text-white">
            Return to dashboard
        </a>
</body>
</html>
