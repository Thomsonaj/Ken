<?php global $base_url; ?>
<!-- BEGIN FORGOT PASSWORD FORM -->
<form class="forget-form" action="<?php print $form['#action']; ?>" method="post">
  <h3 >Forgot Password ?</h3>
  <p>Enter your username or e-mail address below to reset your password.</p>
  <div class="form-group">
    <div class="input-icon">
      <i class="fa fa-envelope"></i>
      <input class="form-control placeholder-no-fix" type="text" autocomplete="off" placeholder="Username or Email" name="name" size="60" maxlength="254"/>
    </div>
  </div>
  <div class="form-actions">
    <a href="<?php print $base_url; ?>/user/login" type="button" id="back-btn" class="btn">
      <i class="m-icon-swapleft"></i> Back
    </a>
    <button type="submit" class="btn green pull-right" id="edit-submit" name="op" >
      Reset <i class="m-icon-swapright m-icon-white"></i>
    </button>
  </div>
</form>
<!-- END FORGOT PASSWORD FORM -->
<?php
print(render($form['form_build_id']));
print(render($form['form_id']));
?>