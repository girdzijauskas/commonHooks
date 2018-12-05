<?php

/**
 * Implements hook_theme_suggestions_container_alter().
 * Adds template suggestions for views.
 */
function d8base_theme_suggestions_container_alter(array &$suggestions, array $variables) {
  if ($variables['element']['#type'] == "view") {
      $pieces = [
          $variables['element']['#type'],
          $variables['element']['#name'],
      ];
      $suggestions[] = 'container__' . implode('_', $pieces);
  }
}


/**
 * Implements hook_theme_suggestions_HOOK_alter().
 * Add views theme suggestions to include the view name and the display name
 */
function p1base_theme_suggestions_views_view_alter(array &$suggestions, array $variables)
{

  $view = $variables['view'];
  $id = $view->storage->id();
  $display_id = $view->current_display;

  $suggestions[] = 'views_view__' . $id;
  $suggestions[] = 'views_view__' . $id . '__' . $display_id;
}