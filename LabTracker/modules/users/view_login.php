<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 7/7/21 5:50 PM
     */
?>
<!doctype html>
<html lang="en">

<head>
    <?php include CORE_PATH . 'assets/inc/meta.php'; ?>
    <?php Core::includeStyles(); ?>
</head>

<body id="<?= $data['_id']?>">
    <?php include CORE_PATH . 'assets/inc/header.php';?>
    <section id="main">
        <div class="aligncenter">
            <div id="loginFormArea">
                <h4>Lab Tracker Admin Login</h4>
                <form class="clearfix margin10Top" id="login" method="post" action="users/login">
                    <div>
                        <div class="errors"></div>
                        <div>
                            <label for="email">Email</label>
                            <input type="email" id="email" name="email" placeholder="username/email">
                        </div>
                        <div>
                            <label for="password">Password</label>
                            <input type="password" id="password" name="password" placeholder="password">
                        </div>
                        <input class="floatright" type="submit" value="Login">
                    </div>
                </form>
            </div>
        </div>
    </section>
    <?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>

</html>