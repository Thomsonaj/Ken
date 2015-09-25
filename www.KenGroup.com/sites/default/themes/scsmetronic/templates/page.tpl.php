<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
global $base_url;
global $user
?>

  <?php if ($logged_in) : ?>
    <!-- BEGIN HEADER -->   
    <div class="header navbar navbar-inverse <?php print $navbar_top; ?>">
      <!-- BEGIN TOP NAVIGATION BAR -->
      <div class="header-inner">
        <!-- BEGIN LOGO -->  
        <?php if ($logo): ?>
          <a class="navbar-brand" href="<?php print $front_page; ?>" title="Home" rel="home">
            <img src="<?php print $logo; ?>" alt="Home" class="img-responsive" />
          </a>
        <?php endif; ?>
        <!-- END LOGO -->
        <!-- BEGIN RESPONSIVE MENU TOGGLER --> 
        <a href="javascript:;" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
          <img src="<?php print $base_url . "/" . path_to_theme(); ?>/assets/img/menu-toggler.png" alt="" />
        </a> 
        <!-- END RESPONSIVE MENU TOGGLER -->
        <!-- BEGIN TOP NAVIGATION MENU -->
        <ul class="nav navbar-nav pull-right">
          <!-- BEGIN NOTIFICATION DROPDOWN -->
          <li class="dropdown" id="header_notification_bar">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown" data-hover="dropdown"
               data-close-others="true">
              <i class="fa fa-warning"></i>
              <span class="badge">0</span>
            </a>
            <ul class="dropdown-menu extended notification">
              <li>
                <p>You have 0 new notifications</p>
              </li>
              <li>

              </li>
              <li class="external">   
                <a href="#">See all notifications <i class="m-icon-swapright"></i></a>
              </li>
            </ul>
          </li>
          <!-- END NOTIFICATION DROPDOWN -->
          <!-- BEGIN INBOX DROPDOWN -->
          <li class="dropdown" id="header_inbox_bar">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown" data-hover="dropdown"
               data-close-others="true">
              <i class="fa fa-envelope"></i>
              <span class="badge">0</span>
            </a>
            <ul class="dropdown-menu extended inbox">
              <li>
                <p>You have 0 new messages</p>
              </li>

              <li class="external">   
                <a href="#">See all messages <i class="m-icon-swapright"></i></a>
              </li>
            </ul>
          </li>
          <!-- END INBOX DROPDOWN -->
          <!-- BEGIN TODO DROPDOWN -->
          <li class="dropdown" id="header_task_bar">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown" data-hover="dropdown" data-close-others="true">
              <i class="fa fa-tasks"></i>
              <span class="badge">0</span>
            </a>
            <ul class="dropdown-menu extended tasks">
              <li>
                <p>You have 0 pending tasks</p>
              </li>
              <li class="external">   
                <a href="#">See all tasks <i class="m-icon-swapright"></i></a>
              </li>
            </ul>
          </li>
          <!-- END TODO DROPDOWN -->
          <!-- BEGIN USER LOGIN DROPDOWN -->
          <li class="dropdown user">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown" data-hover="dropdown" data-close-others="true">
              <?php if(!empty($variables['image'])) { ?>
              <img alt="" src="<?php print file_create_url($variables['image']);?>" width="29" height="29"/>
              <?php }  else{ ?>
              <img alt="" src="<?php print $base_url . "/" . path_to_theme(); ?>/assets/img/avatar_small.png"/>
              <?php } ?>
              <span class="username"><?php print $loggedin_user_name; ?></span>
              <i class="fa fa-angle-down"></i>
            </a>
            <?php
            print theme('links__system_user_menu', array(
              'links' => $user_menu_expanded,
              'attributes' => array(
                'id' => 'user-menu',
                'class' => array('nav', 'clearfix'),
              ),
              'heading' => array(
                'text' => t('User Menu'),
                'level' => 'h2',
                'class' => array('element-invisible'),
              ),
            ));
            ?>
          </li>
          <!-- END USER LOGIN DROPDOWN -->
        </ul>
        <!-- END TOP NAVIGATION MENU -->
      </div>
      <?php if(!empty($page['content_frozen'])): ?>
    <div id="content-frozen"><?php print render($page['content_frozen']);?></div>
    <?php endif; ?>
      <!-- END TOP NAVIGATION BAR -->
    </div>
    <!-- END HEADER -->
    <!-- BEGIN CONTAINER -->
    <!--<div id="main" <?php //if(!empty($page['content_frozen'])) { print "class='has-frozenpane'";} ?>>-->
    <?php if ($page['sidebar_first'] || !empty($main_menu_expanded)): ?>   
      <div class="page-container">
        <!-- BEGIN SIDEBAR -->
        <div class="page-sidebar navbar-collapse collapse">
          <!-- BEGIN SIDEBAR MENU -->        	
          <?php
          print theme('links__system_main_menu', array(
            'links' => $main_menu_expanded,
            'attributes' => array(
              'id' => 'main-menu',
              'class' => array('nav', 'clearfix'),
            ),
            'heading' => array(
              'text' => t('Main Menu'),
              'level' => 'h2',
              'class' => array('element-invisible'),
            ),
          ));
          ?>
          <!-- END SIDEBAR MENU -->
          <?php print render($page['sidebar_first']); ?>
        </div>
      <?php endif; ?>
      <!-- END SIDEBAR -->

      <!-- BEGIN PAGE -->
      <!--creating a class for he right side bar-->
      <?php $class = "";
      if($page['sidebar_second']) {
        $class = 'right-side';
      }
      ?>
      <div class="page-content <?php print $class;?>">
        <!-- BEGIN SAMPLE PORTLET CONFIGURATION MODAL FORM--> 
        <div id="forms-modal" class = "modal hide">
          <div id="waiting_modal">
            <div class="modal-header"> <button type="button" class="close" data-dismiss="modal">×</button>
              <h3> <?php print t('Please wait...'); ?> </h3>
            </div>
            <div class="modal-body">
              <div class="progress progress-striped active">
                <div class="bar" style="width: 100%;"></div>
              </div>
            </div>
          </div>
          <div id="content_modal"></div>
        </div>

        <div class="row">
          <div class="col-md-12">
            <!-- BEGIN PAGE TITLE & BREADCRUMB-->		
            <a id="main-content"></a>
            <?php print render($title_prefix); ?>
            <?php if ($title): ?><h3 class="page-title"><?php print $title; ?></h3><small></small><?php endif; ?>
            <?php print render($title_suffix); ?>

            <?php // if ($breadcrumb): ?>
              <?php // print $breadcrumb; ?>
            <?php // endif; ?>
            <?php print $messages; ?>
            <!--<a  href="#portlet-config" data-toggle="modal">Ganesha</a>-->
            <!-- END PAGE TITLE & BREADCRUMB-->
          </div>
        </div>
        <!-- END PAGE HEADER-->
        <!-- BEGIN PAGE CONTENT-->
        <div class="row">
          <div class="col-md-12">
            <a id="main-content"></a>

            <?php if ($tabs): ?><div class="tabbable-custom"><?php print render($tabs); ?></div><?php endif; ?>
            <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
            <?php print render($page['content']); ?>
            <?php print $feed_icons; ?>

          </div>
          <!-- END PAGE CONTENT-->

        </div>
      </div>
      <!-- END PAGE -->    

      <!--BEGIN RIGHT SIDE BAR-->
      <?php if ($page['sidebar_second']): ?>   
        <div class="right-sidebar contextual-links-region">
          <?php print render($page['sidebar_second']); ?>
        </div>
      <?php endif; ?>

      <!--END RIGHT SIDE BAR-->
    </div>
<!--</div>-->
    <!-- END CONTAINER -->
    <!-- BEGIN FOOTER -->
    <div class="footer">
      <div class="footer-inner">
        <?php print date('Y');?> &copy; <?php print variable_get('site_name');?>
      </div>
      <div class="footer-tools">
        <span class="go-top">
          <i class="fa fa-angle-up"></i>
        </span>
      </div>
    </div>
    <!-- END FOOTER -->
  <?php else : ?>
    <!-- BEGIN LOGO -->
    <div class="logo">
      <a href="<?php print $front_page; ?>" title="Home" rel="home">
        <!--<img src="<?php //print $base_url . "/" . path_to_theme();    ?>/assets/img/logo-big.png" alt="Home" />--> 
      </a>

    </div>
    <!-- END LOGO -->
    <!-- BEGIN LOGIN -->
    <?php if (!empty($messages)) : ?>
      <div class="login_msg_content">
        <?php print $messages; ?>
      </div>
    <?php endif; ?>
    <?php print render($page['content']); ?>
    <!-- END LOGIN -->
    <!-- BEGIN COPYRIGHT -->
    <div class="copyright">
      <?php print date('Y');?> &copy <?php print variable_get('site_name');?>
    </div>
    <!-- END COPYRIGHT -->
  <?php //endif; ?>
<?php endif; ?>