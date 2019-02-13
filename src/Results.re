Random.self_init();

/* a piece of the global state
   this component is 'interested' in*/
type ctx = {
  isLoading: bool,
  results: Root.list_of_repos,
};

let component = ReasonReact.statelessComponent("Results");

let make = (~ctx: ctx, _children) => {
  ...component,
  render: _self =>
    <div>
      {
        ctx.isLoading ?
          ReasonReact.string("Loading...") :
          ctx.results
          /* Convert to list to an array for ReasonReact's type bindings */
          |> Array.of_list
          /* Map each array item to a <Card /> component */
          |> Array.map(({name, href, description}: Root.repository) =>
               <Card
                 key={string_of_int(Random.int(500)) ++ href}
                 name
                 href
                 description
               />
             )
          /* Transform the array into a valid React node, similar to ReasonReact.string */
          |> ReasonReact.array
      }
    </div>,
};