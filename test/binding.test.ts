import torch from '../src/binding';

describe('binding', () => {
  it('module should load', () => {
    expect(torch).not.toBeNull();
    console.log(torch);
  });
});
