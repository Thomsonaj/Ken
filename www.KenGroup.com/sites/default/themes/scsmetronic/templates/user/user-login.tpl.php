<?php global $base_url; ?>
<!-- BEGIN LOGIN FORM -->
<form class="login-form" action="<?php print $form['#action']; ?>" method="post">
  <h3 class="form-title">Login to your account</h3>
  <div class="form-group">
    <!--ie8, ie9 does not support html5 placeholder, so we just show field title for that-->
    <label class="control-label visible-ie8 visible-ie9">Username</label>
    <div class="input-icon">
      <i class="fa fa-user"></i>
      <input class="form-control placeholder-no-fix" type="text" autocomplete="off" placeholder="Username" name="name"/>
    </div>
  </div>
  <div class="form-group">
    <label class="control-label visible-ie8 visible-ie9">Password</label>
    <div class="input-icon">
      <i class="fa fa-lock"></i>
      <input class="form-control placeholder-no-fix" type="password" autocomplete="off" placeholder="Password" name="pass"/>
    </div>
  </div>
  <div class="form-actions">
    <button type="submit" class="btn green pull-right" id="edit-submit" name="op" >
      Login <i class="m-icon-swapright m-icon-white"></i>
    </button>           
  </div>
  <div class="forget-password">
    <h4>Forgot your password ?</h4>
    <p>
      no worries, click <a href="<?php print $base_url; ?>/user/password"  id="forget-password">here</a>
      to reset your password.
    </p>
  </div>
  <?php if (variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL)) : ?>
    <div class="create-account">
      <p>
        Don't have an account yet ?&nbsp; 
        <a href="<?php print $base_url; ?>/user/register" id="register-btn" >Create an account</a>
      </p>
    </div>
  <?php endif; ?>
</form>
<!-- END LOGIN FORM --> 
<?php
print(render($form['form_build_id']));
print(render($form['form_id']));
//print(render($form['actions']));
?>