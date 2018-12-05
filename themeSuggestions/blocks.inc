<?php

function p1base_theme_suggestions_block_alter(array &$suggestions, array $variables)
{

  // Adding a custom block theme suggestion to include the bundle (type) of the
  // block
  if (isset($variables['elements']['content']['#block_content'])) {
    array_splice($suggestions, 1, 0, 'block__bundle__' . $variables['elements']['content']['#block_content']->bundle());
  }
}

// Hooks and code related to theme suggestions
function p1base_theme_suggestions_block_alter2(array &$suggestions, array $variables) {
  $node = \Drupal::request()->attributes->get('node');

  // Add block suggestions based on what is the conten
  if ($node) {
    $bundle = $node->bundle();
    $suggestions[] = 'block__' . $bundle . '__' . $variables['elements']['#plugin_id'];
  }

  $block = $variables['elements'];
  $blockType = $block['#configuration']['provider'];
  if ($blockType == "block_content") {
      $bundle = $block['content']['#block_content']->bundle();
      $id = $block['content']['#block_content']->id();
      $suggestions[] = 'block__' . $blockType;
      $suggestions[] = 'block__' . $blockType . '__' . $bundle;
      $suggestions[] = 'block__' . $id;
  }
}