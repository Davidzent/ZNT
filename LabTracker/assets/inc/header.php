<?php
	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/21/2018 20:11
	 */
	include CORE_PATH . 'assets/inc/notice.php';
?>
<header class="clearfix">
	<div class="title">
		<a href="<?=CORE_URL?>"><p>Lab Tracker</p></a>
	</div>
    <?php
        if( $GLOBALS['app']->users->isLoggedIn() ){
            ?><div class="user">
                <span class="name"><?= ucwords( $_SESSION['session']['name'] )?></span>
                <span class="logout margin5Right margin5Left" title="Logout"><a href="<?=CORE_URL?>users/logout"><i class="fas fa-sign-out-alt"></i></a></span>
            </div> <?php
        } else {
            ?><div class="user">
            <span class="login margin5Right margin5Left" title="Logout"><a href="<?=CORE_URL?>users/login">Login</a></span>
            </div> <?php
        }
    ?>
</header>
