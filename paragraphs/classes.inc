<?php


/**
 * Implements hook_preprocess_paragraph().
 * Takes the field value of Classes inside the CP Element Paragraph and passes
 * it down to the twig template immediately.
 */
function d8base_preprocess_paragraph(&$variables) {
  if ($variables['paragraph']->field_classes) {
    $custom_classes = $variables['paragraph']->field_classes->value;
    $exploded_classes = explode(" ", $custom_classes);
    $variables['d8base_custom_classes'] = $exploded_classes;
  }

  if ($variables['paragraph']->field_home_link) {
    // Preprocesses the stupid home_link URI into a usable URL value.
    $url = Url::fromUri($variables['paragraph']->field_home_link[0]->uri);
    $variables['home_link_url'] = $url; // WTF IS UP WITH THIS SHIT
  }

  // Adds an ID with the heading of the paragraph to the paragraph element.
  // This means that other pages can link to this element from any other
  // place on the site.
  if ($variables['paragraph']->field_id_link) {
    if ($variables['paragraph']->field_id_link->value !== 0) {
        $heading = $variables['paragraph']->field_heading->value;
        $heading_lower = strtolower($heading);
        $variables['id_link'] = str_replace(' ', '-', $heading_lower);
    }
  }
}

function p1base_preprocess_paragraph(&$variables)
{

  // Takes the Classes field value and gives it to the template to utilise within
  // the attributes array as a custom per-paragraph class.
  //  FIXME:  instead of creating my own custom variable that is printed in the
  // template, you should be adding this *DIRECTLY* to the attributes array
  if ($variables['paragraph']->field_classes) {
    $custom_classes = $variables['paragraph']->field_classes->value;
    $exploded_classes = explode(" ", $custom_classes);
    $variables['custom_classes'] = $exploded_classes;
  }


  // Takes the Color field value and gives it to the template to utilise within the
  // attributes array.
  //  FIXME:  same as above. Don't use custom variable, utilise the attributes
  // array instead, which exists in the template already.
  if ($variables['paragraph']->field_color) {
    $color_class = $variables['paragraph']->field_color->value;
    $variables['custom_classes'][] = $color_class;
  }

  // Pass down the URL from the link field to the template directly.
  if ($variables['paragraph']->field_link) {
    $link_url = $variables['paragraph']->field_link->uri;
    $variables['link_url'] = $link_url;
  }

  /**
 * Implements HOOK_preprocess_ENTITY
 * NOTE: you should improve this by adding directly to the classes instead of
 * creating a new variable yourself.
 */
function p1base_preprocess_paragraph(&$variables) {
  if ($variables['paragraph']->field_classes) {
      $custom_classes = $variables['paragraph']->field_classes->value;
      $exploded_classes = explode(" ", $custom_classes);
      $variables['custom_classes'] = $exploded_classes;
  }

  $value_fields = [
    'field_title_line',
    'field_strip_default_classes',
    'field_x_swap',
    'field_y_swap',
    'field_z_swap',
  ];

  foreach ($value_fields as $field) {
    if ($variables['paragraph']->$field) {
        $$field = $variables['paragraph']->$field->value;
        $variables[$field] = $$field;
    }
  }
}

function p1base_preprocess_field(&$variables) {
  if($variables['field_name'] == 'field_elements'){
   foreach($variables['items'] as $idx => $item) {
      $variables['items'][$idx]['content']['#paragraph']->index = $idx;
    }
  }
}
