<div class="view-invoice-order-details-form">
    <?php print drupal_render($form['table']); ?>
    <?php print drupal_render($form['blank1']); ?>
    <?php //print drupal_render($form['group_date']); ?>
</div>
    <table frame="void">
        <tbody>
            <tr></tr>
            <tr>
                <td><b>&nbsp;&nbsp;<?php print($form['group_date']['ken_promise_date']['#title']); ?></b></td>
                <td><b>&nbsp;&nbsp;<?php print($form['group_date']['customer_promise_date']['#title']); ?></b></td>
                <td><b>&nbsp;&nbsp;<?php print($form['group_date']['collection_date']['#title']); ?></b></td>
                <td><b>&nbsp;&nbsp;<?php print($form['group_date']['follow_thru_date']['#title']); ?></b></td>
            </tr>
            <tr>
                <td><?php print drupal_render($form['group_date']['ken_promise_date']); ?></td>
                <td><?php print drupal_render($form['group_date']['customer_promise_date']); ?></td>
                <td><?php print drupal_render($form['group_date']['collection_date']); ?></td>
                <td><?php print drupal_render($form['group_date']['follow_thru_date']); ?></td>

            </tr>
        </tbody>
    </table>





<table frame="void">
    <tbody>
        <tr>
            <td> <?php print drupal_render($form['current_email']); ?></td>
            <td>&nbsp;&nbsp;&nbsp;&nbsp;</td>
            <td> <?php print drupal_render($form['current_phone']); ?></td>
        </tr>
        <tr>
            <td> <?php print drupal_render($form['status']); ?></td>
            <td>&nbsp;&nbsp;&nbsp;&nbsp;</td>
            <td> <?php print drupal_render($form['collectable']); ?></td>
        </tr>
    </tbody>
</table>

<div class="view-invoice-order-details-form">
    <?php print drupal_render_children($form); ?>
</div>
