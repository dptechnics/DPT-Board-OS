/* 
 * Authors: Matthieu Calie, Daan Pape
 * This file contains the custom blocks for blockly to power the DPT-Robot module
 */

/*
 * Custom Block 1 : Robot forward moving
 * https://blockly-demo.appspot.com/static/demos/blockfactory/index.html#vao53d
 */
Blockly.Blocks['robot_move'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(210);
    this.appendValueInput("MOVE")
        .setCheck("Number")
        .appendField("Move robot")
        .appendField(new Blockly.FieldDropdown([["Forward", "UP"], ["Backward", "DOWN"], ["Left", "LEFT"], ["Right", "RIGHT"]]), "DIRECTION")
        .appendField("For");
    this.appendDummyInput()
        .appendField(" * 100 ms");
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
    this.setTooltip('');
  }
};
/*
 * Custom Block 2 : Robot spinning movement
 * https://blockly-demo.appspot.com/static/demos/blockfactory/index.html#sogg5d
 */
Blockly.Blocks['robot_spin'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(210);
    this.appendDummyInput()
        .appendField("Spin Robot 90°");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["Left", "LEFT"], ["Right", "RIGHT"]]), "SPIN");
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
    this.setTooltip('');
  }
};
/*
 * Custom Block  3: DPT-Board change pin state
 * https://blockly-demo.appspot.com/static/demos/blockfactory/index.html#PMG7H2
 */
Blockly.Blocks['digitalWrite'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(210);
    this.appendDummyInput()
        .appendField("Pin");
    this.appendValueInput("PIN")
        .setCheck("Number");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["enable", 1], ["disable", 0]]), "STATE");
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
    this.setTooltip('');
  }
};

/*
 * Custom block : Set TimeOut function
 * https://blockly-demo.appspot.com/static/demos/blockfactory/index.html#42fjq3
 */
Blockly.Blocks['controls_settimeout'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(120);
    this.appendDummyInput()
        .appendField("SetTimeOut");
    this.appendValueInput("TIME")
        .setCheck("Number");
    this.appendDummyInput()
        .appendField("ms");
    this.appendStatementInput("branch")
        .setCheck("null");
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
    this.setTooltip('');
  }
};


Blockly.JavaScript['robot_move'] = function(block) {
  var value_move = Blockly.JavaScript.valueToCode(block, 'MOVE', Blockly.JavaScript.ORDER_ATOMIC);
  var dropdown_direction = block.getFieldValue('DIRECTION');
  // TODO: Assemble JavaScript into code variable.
  var code;
  switch (dropdown_direction) {
      case "UP":
          code = "moveForward(" + value_move + ");";
          break;
      case "DOWN":
          code = "moveBackward(" + value_move + ");";
          break;
      case "LEFT":
          code = "moveLeft(" + value_move + ");";
          break;
      case "RIGHT":
          code = "moveRight(" + value_move + ");";
          break;
      default:
          code = "waiting for input";          
  }
  code += "\n"
  return code;
};

Blockly.JavaScript['robot_spin'] = function(block) {
  var dropdown_spin = block.getFieldValue('SPIN');
  var code;
  switch (dropdown_spin) {
      case "LEFT":
          code = "spinLeft();";
          break;
      case "RIGHT":
          code = "spinRight();";
          break;
      default:
          code = "waiting for input";          
  }
  code += "\n"
  return code;
};

Blockly.JavaScript['digitalWrite'] = function(block) {
  var value_pin = Blockly.JavaScript.valueToCode(block, 'PIN', Blockly.JavaScript.ORDER_ATOMIC);
  var value_state = Blockly.JavaScript.valueToCode(block, 'STATE', Blockly.JavaScript.ORDER_ATOMIC);
  var dropdown_status = block.getFieldValue('STATUS');
  var code;
  switch (dropdown_status) {
      case "ENABLE":
          code = "digitalWrite(" + value_pin + ", " + value_state + " );";
          break;
      case "DISABLE":
          code = "digitalWrite(" + value_pin + ");";
          break;
      default:
          code = "Waiting for input";
  }
  code += "\n";
  return code;
};

Blockly.JavaScript['text_print'] = function(block) {
  // Print statement.
  var argument0 = Blockly.JavaScript.valueToCode(block, 'TEXT',
      Blockly.JavaScript.ORDER_NONE) || '\'\'';
  return 'console.log(' + argument0 + ');\n';
};

Blockly.JavaScript['controls_settimeout'] = function(block) {
  var value_time = Blockly.JavaScript.valueToCode(block, 'TIME', Blockly.JavaScript.ORDER_ATOMIC);
  var statements_branch = Blockly.JavaScript.statementToCode(block, 'branch');
  
  var code = "setTimeout(function() { \n " + statements_branch + "}, " + value_time + ");\n";
  return code;
};

Blockly.JavaScript['function_thread'] = function(block) {
  var statements_thread = Blockly.JavaScript.statementToCode(block, 'THREAD');
  var code = 'setTimeout(function() {\n' + statements_thread + '}, 0);\n';
  return code;
};

Blockly.JavaScript['function_wait'] = function(block) {
  var value_time = Blockly.JavaScript.valueToCode(block, 'TIME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
  var code = 'hold(' + value_time + ')\n';
  return code;
};


