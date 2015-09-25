<table frame="void">
    <tbody>

        <tr> <td><?php print drupal_render($form['user']); ?></td><td>&nbsp;&nbsp;</td>
            <td><?php print drupal_render($form['client']); ?></td><td>&nbsp;&nbsp;</td>
            <td><?php print drupal_render($form['status']); ?></td><td>&nbsp;&nbsp;</td>
            <td><?php //print drupal_render($form['collection_status']); ?></td>
            <td><?php print drupal_render($form['financial_year']); ?></td><td>&nbsp;&nbsp;</td>
            <td><?php print drupal_render($form['quarter']); ?></td>
        </tr>

        <tr><td><?php print drupal_render($form['filter']); ?>&nbsp;&nbsp;
                <?php print drupal_render($form['reset']); ?></td>
        </tr>
    </tbody>
</table>

<div class="view-invoice-totals-form">	  



    <?php print drupal_render_children($form);
    ?>  
</div>

