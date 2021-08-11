export default class GetTime {
    constructor() {
        this.now = new Date();
        this.hour = this.now.getHours();
        this.min = this.now.getMinutes();
        this.sec = this.now.getSeconds();
    }

    show() {
        alert(`${this.hour}:${this.min}:${this.sec}`);
    }
}
