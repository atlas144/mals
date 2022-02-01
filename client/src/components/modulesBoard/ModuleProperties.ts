export default class ModuleProperties {
  public i: string;
  public identifier: string;
  public w: number;
  public minW = 3;
  public h: number;
  public minH = 2;
  public x = 0;
  public y = 0;

  public constructor(
    name: string,
    identifier: string,
    width: number,
    height: number
  ) {
    this.i = name;
    this.identifier = identifier;
    this.w = width;
    this.h = height;
  }
}
