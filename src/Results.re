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
          /* Map each list item to a <Card /> component */
          |> List.mapi(
               (index: int, {name, href, description}: Root.repository) =>
               <Card key={string_of_int(index)} name href description />
             )
          /* covert to Array before going to DOM */
          |> Array.of_list
          /* Transform the array into a valid React node, similar to ReasonReact.string */
          |> ReasonReact.array
      }
    </div>,
};