<?php


function p1base_preprocess(&$variables, $hook) {
  // Add 'is_front' variable flag to every template on the site.
  try {
    $variables['is_front'] = \Drupal::service('path.matcher')->isFrontPage();
  } catch (Exception $e) {
    $variables['is_front'] = false;
  }
  // Ensure the cache varies correctly (new in Drupal 8.3).
  $variables['#cache']['contexts'][] = 'url.path.is_front';
}
