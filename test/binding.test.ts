// import { sum } from '../src';

// describe('blah', () => {
//   it('works', () => {
//     expect(sum(1, 1)).toEqual(2);
//   });
// });

// const torch = require('../lib/binding');
import torch from '../src/binding';

describe('binding', () => {
  it('module should load', () => {
    expect(torch).not.toBeNull();
    console.log(torch);
  });
});
