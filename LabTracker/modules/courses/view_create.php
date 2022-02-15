<?php
?>
<!doctype html>
<html lang="en">

<head>
    <?php include CORE_PATH . 'assets/inc/meta.php'; ?>
    <?php Core::includeStyles(); ?>
</head>
    <?php if( $GLOBALS['app']->users->isLoggedIn() ){ ?>
<body id="<?= $data['_id']?>">
    <?php include CORE_PATH . 'assets/inc/header.php';?>
    <section id="main">
        <div class="aligncenter">
            <div id="kioskFormArea">
                <form id="ClassAction" name = 'file' method="post" action="courses/create" enctype="multipart/form-data">
                    <div class="classcreate">
                        <label>
                        <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="CreateOne" type="button" value="Create One Course" />' ?> 
                        <?php if( Core::hasRole( users::ADMIN ) ) echo '<input id="Create" type="button" value="Create Courses"/>' ?> 
                        </label>
                    </div>
                    
                    <div class="results"></div>
                    <div class="filters"></div>
                    <div class="adminphase2 none"></div>
                    <div class="adminphase2pages"></div>
                </form>
                
            </div>
        </div>
    </section>
    <?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>
 <?php } ?>
</html>