<?php

/**
 * Implements HOOK_preprocess_HOOK
 * This hook means that if the page has a field_banner_image, the image that is
 * uploaded there will turn into the background for the title. This machine
 * name should be the one being used to created the banner images behind the
 * title.
 *
 * This hook works for both a node page and a view page - the node version relies
 * on a field_banner_image, and the view page version needs a block in the title
 * region of a type 'view_title' with the banner image uploaded there.
 */
function p1base_preprocess_block__page_title_block(&$variables) {
  // Fetch current route name
  $current_route_name = \Drupal::service('current_route_match')->getRouteName();
  preg_match('/^[^.]+/', $current_route_name, $matches);


  // Which pages to enable this for? What kind of view pages will we come across?
  $view_pages = [
    'view',
    'search',
  ];

  // Checks if the route is a view page.
  if (in_array($matches[0], $view_pages)) {

    $visible_blocks = \Drupal::service('block.repository')->getVisibleBlocksPerRegion();
    $title_blocks = $visible_blocks['title']; // We only want to look at the blocks that are in the Title region.

    // We should filter the title_blocks array to block_content blocks only.
    foreach($title_blocks as $title_block) {
      $plugin = $title_block->getPlugin();

      if (is_a($plugin, 'Drupal\block_content\Plugin\Block\BlockContentBlock')) { // Check if it's a block_content block
        $derivative_id = $plugin->getDerivativeId();
        $block = \Drupal::entityManager()->loadEntityByUuid('block_content', $derivative_id);
        $bundle = $block->bundle();
        if ($bundle == 'view_title') { // The machine name for the block types which I will use to give background images to blog page titles
          $banner_url = file_create_url($block->field_background_image->entity->getFileUri());
          $variables['banner_url'] = $banner_url;
        }
      }
    }
  }

  // if not a view page, then a node page?
  else {

    $node = \Drupal::request()->attributes->get('node');

    if (method_exists($node, 'hasField')) { // Need this check to avoid notices

      if ($node->hasField('field_title_class')) {
        if (!$node->get('field_title_class')->isEmpty()) {
          $title_class = $node->get('field_title_class')->value;
          $exploded_classes = explode(" ", $title_class);
          // $variables['field_title_class'] = $title_class;
          foreach($exploded_classes as $class) {
            $variables['title_classes'][] = $class;
          }
        }
      }

      // Render fields
      $render_fields = [ // Machine names of fields to pass onto the page title template as full render arrays
        'field_title_image',
        'field_parent_title',
        'body'
      ];

      // Value fields
      $value_fields = [ // Machine names of fields to pass onto the page title template as values only
        'field_x_swap',
        'field_z_swap',
      ];

      $view_settings = ['label' => 'hidden'];

      foreach ($render_fields as $field) {
        if ($node->hasField($field)) {
          if (!$node->get($field)->isEmpty()) {
            $$field = $node->get($field)->view($view_settings);
            $variables[$field] = $$field;
          }
        }
      }

      foreach ($value_fields as $field) {
        if ($node->hasField($field)) {
          if (!$node->get($field)->isEmpty()) {
            $$field = $node->get($field)->value;
            $variables[$field] = $$field;
          }
        }
      }
    }
  }
}