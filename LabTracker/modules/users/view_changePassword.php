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
                <h4>Change Password</h4>
                <form class="clearfix margin10Top" id="changePass" method="post" action="users/changePassword">
                    <div>
                        <div class="errors"></div>
                        <div>
                            <label class="alignleft" for="password">Old Password</label>
                            <input type="password" id="password" name="password" placeholder="Password">
                        </div>
                        <div class="relative">
                            <div class="none passwordPopover">
                                <div>
                                    <p><span class="length"><i class="fa red fa-times"></i></span> 10 Characters length</p>
                                    <p><span class="upper"><i class="fa red fa-times"></i></span> Uppercase letter</p>
                                    <p><span class="lower"><i class="fa red fa-times"></i></span> Lowercase letter</p>
                                    <p><span class="number"><i class="fa red fa-times"></i></span> Number</p>
                                    <p><span class="symbol"><i class="fa red fa-times"></i></span> Symbol</p>
                                </div>
                            </div>
                            <label class="alignleft" for="newPassword">Password</label>
                            <input type="password" class="hints" id="newPassword" name="newPassword" placeholder="New password" data-confirm="confirmPass">
                        </div>
                        <div class="relative">
                            <label class="alignleft" for="confirmPass">Confirm Password</label>
                            <input type="password" class="" id="confirmPass" placeholder="Confirm password" data-type="password">
                        </div>
                        <input class="floatright" type="submit" value="Change Password">
                    </div>
                </form>
            </div>
        </div>
    </section>
    <?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>

</html>