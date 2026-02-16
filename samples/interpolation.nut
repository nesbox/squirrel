local userName = "Bob";
print(`Hello ${userName}!`);

local a = 10;
local b = 20;
print(`The sum of ${a} and ${b} is ${a + b}.`);

local table_val = {key = "value"};
print(`Table value: ${table_val.key}`);

// Test with no expressions
print(`Just a plain string.`);

// Test with only expressions
print(`${1 + 1}`);