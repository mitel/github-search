let component = ReasonReact.statelessComponent("Card");

let make = (~name, ~href, ~description, _children) => {
  ...component,
  render: _self =>
    <div className="card">
      <div className="card-image">
        <figure className="image is-4by3">
          <img
            src="https://versions.bulma.io/0.7.0/images/placeholders/1280x960.png"
            alt="Placeholder image"
          />
        </figure>
      </div>
      <div className="card-content">
        <div className="media">
          <div className="media-left">
            <figure className="image is-48x48">
              <img
                src="https://versions.bulma.io/0.7.0/images/placeholders/96x96.png"
                alt="Placeholder image"
              />
            </figure>
          </div>
          <div className="media-content">
            <p className="subtitle is-6"> {ReasonReact.string(name)} </p>
          </div>
        </div>
        <div className="content">
          {ReasonReact.string(description)}
          <br />
          {ReasonReact.string(href)}
          <time dateTime="2016-1-1" />
        </div>
      </div>
    </div>,
};
